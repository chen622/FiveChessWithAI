/*
 * https://github.com/tashaxing/CppHttpDemo
 */

#ifndef THIRDPARTY_HTTP_SERVER_H_
#define THIRDPARTY_HTTP_SERVER_H_

#include <string>
#include <unordered_map>
#include <functional>
#include "mongoose.h"

// 定义http返回callback
typedef void OnRspCallback(mg_connection *c, const char *, std::string);
// 定义http请求handler
using ReqHandler = std::function<bool(std::string, std::string, mg_connection *c, OnRspCallback)>;

class HttpServer {
 public:
  HttpServer() {}
  ~HttpServer() { Close(); }
  void Init(const std::string &port); // 初始化设置
  bool Start(); // 启动httpserver
  bool Close(); // 关闭
  void AddHandler(const std::string &url, ReqHandler req_handler); // 注册事件处理函数
  void RemoveHandler(const std::string &url); // 移除事件处理函数

 public:
  static std::string s_web_dir; // 网页根目录
  static mg_serve_http_opts s_server_option; // web服务器选项
  static std::unordered_map<std::string, ReqHandler> s_handler_map; // 回调函数映射表

 private:
  // 静态事件响应函数
  static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);
  static void HandleEvent(mg_connection *connection, http_message *http_req);
  static void SendRsp(mg_connection *connection, const char *status, std::string rsp); // status是响应状态码

 private:
  std::string m_port;    // 端口
  mg_mgr m_mgr;          // 连接管理器
};

#endif  //THIRDPARTY_HTTP_SERVER_H_
