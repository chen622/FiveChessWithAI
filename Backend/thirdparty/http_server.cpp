/*
 * https://gitlab.com/zhsun/cpp_mongoose_webserver_demo
 */
#include <utility>
#include "http_server.h"

// 初始化HttpServer静态类成员
#if defined(__unix__) || defined(__APPLE__)
std::string HttpServer::s_web_dir = "../web"; //web根目录
#elif defined(_WIN32)
std::string HttpServer::s_web_dir = "../web"; //web根目录
#endif
mg_serve_http_opts HttpServer::s_server_option;
std::unordered_map<std::string, ReqHandler> HttpServer::s_handler_map;

//static bool route_check(http_message *http_msg, char *route_prefix)
//{
//    if (mg_vcmp(&http_msg->uri, route_prefix) == 0)
//        return true;
//    else
//        return false;

//    // TODO: 还可以判断 GET, POST, PUT, DELTE等方法
//    //mg_vcmp(&http_msg->method, "GET");
//    //mg_vcmp(&http_msg->method, "POST");
//    //mg_vcmp(&http_msg->method, "PUT");
//    //mg_vcmp(&http_msg->method, "DELETE");
//}

struct mg_str upload_fname(struct mg_connection *nc, struct mg_str fname) {
  // TO DO: 根据文件名称，重新指定文件保存路径+文件名
  return fname;
}

void HttpServer::Init(const std::string &port) {
  m_port = port;
  s_server_option.enable_directory_listing = "yes";
  s_server_option.document_root = s_web_dir.c_str();
  // TODO：其他设置
}

bool HttpServer::Start() {
  mg_mgr_init(&m_mgr, NULL);
  mg_connection *connection = mg_bind(&m_mgr, m_port.c_str(), OnHttpEvent);
  if (connection == NULL) {
    printf("bind error, using port: %s\n", m_port.c_str());
    return false;
  }
  mg_set_protocol_http_websocket(connection);

  printf("starting http server at port: %s\n", m_port.c_str());
  // loop
  while (true)
    mg_mgr_poll(&m_mgr, 500); // ms

  return true;
}

void HttpServer::OnHttpEvent(mg_connection *connection, int event_type, void *event_data) {
  http_message *http_req = (http_message *) event_data;
  switch (event_type) {
    case MG_EV_HTTP_REQUEST: {
      HandleEvent(connection, http_req);
      break;
    }
      /* 接收POST方式，提交上传上来的文件，并转存下来 */
    case MG_EV_HTTP_PART_BEGIN:
    case MG_EV_HTTP_PART_DATA:
    case MG_EV_HTTP_PART_END: {
      struct mg_http_multipart_part *mp =
          (struct mg_http_multipart_part *) event_data;
      printf("file_name: %s, var_name: %s, status: %d\n",
             mp->file_name, mp->var_name, mp->status);
      mg_file_upload_handler(connection, event_type, event_data, upload_fname);
      break;
    }
    default:break;
  }
}

void HttpServer::AddHandler(const std::string &url, ReqHandler req_handler) {
  if (s_handler_map.find(url) != s_handler_map.end())
    return;

  s_handler_map.insert(std::make_pair(url, req_handler));
}

void HttpServer::RemoveHandler(const std::string &url) {
  auto it = s_handler_map.find(url);
  if (it != s_handler_map.end())
    s_handler_map.erase(it);
}

void HttpServer::SendRsp(mg_connection *connection, const char *status, std::string rsp) {
  // 必须先发送header
  mg_printf(connection, "HTTP/1.1 %s\r\nTransfer-Encoding: chunked\r\n\r\n", status);
  // 以json形式返回
  mg_printf_http_chunk(connection, "{ \"result\": %s }", rsp.c_str());
  // 发送空白字符快，结束当前响应
  mg_send_http_chunk(connection, "", 0);
}

void HttpServer::HandleEvent(mg_connection *connection, http_message *http_req) {
  std::string req_str = std::string(http_req->message.p, http_req->message.len);
  std::string body = std::string(http_req->body.p, http_req->body.len);
  std::string query_string = std::string(http_req->query_string.p, http_req->query_string.len);

//  printf("got request:\n%s\n", req_str.c_str());
//  printf("body:        %s\n", body.c_str());
//  printf("query_string:%s\n", query_string.c_str());

  // 先过滤是否已注册的函数回调
  std::string url = std::string(http_req->uri.p, http_req->uri.len);
  auto it = s_handler_map.find(url);
  if (it != s_handler_map.end()) {
    ReqHandler handle_func = it->second;
    handle_func(body,
                query_string, /* 动态请求,？号后面的内容 */
                connection, SendRsp);
    return;
  }

  // 其他请求,主要处理html页面打开请求
  char file[100];
  strcpy(file, s_web_dir.c_str());
  if (url == "/") {
    strcat(file, "/index.html");
    url = "/index.html";
  } else
    strcat(file, url.c_str());

  struct stat filestat;
  int ret = stat(file, &filestat);
  if (ret < 0 || S_ISDIR(filestat.st_mode)) //file doesn't exits
  {
    mg_printf(
        connection,
        "%s",
        "HTTP/1.1 501 Not Implemented\r\n"
        "Content-Length: 0\r\n\r\n");
  } else {
    s_server_option.index_files = url.c_str();
    mg_serve_http(connection, http_req, s_server_option);
  }
}

bool HttpServer::Close() {
  mg_mgr_free(&m_mgr);
  return true;
}
