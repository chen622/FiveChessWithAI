/*
 * MIT License
 * 
 * Copyright (c) 2020 Chenming C (ccm@ccm.ink)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include "http_server.h"
#include <memory>
#include <string>
#include <iostream>

bool handle_fun1(std::string body, std::string query_string, mg_connection *c, OnRspCallback reply_callback) {
  std::cout << "FUNC: " << __FUNCTION__ << "  "
            << "body: " << body << std::endl;
  std::cout << "FUNC: " << __FUNCTION__ << "  "
            << "query_string: " << query_string << std::endl;

  reply_callback(c, "200 OK", "success");

  return true;
}

bool handle_fun2(std::string body, std::string query_string, mg_connection *c, OnRspCallback reply_callback) {
  std::cout << "FUNC: " << __FUNCTION__ << "  "
            << "body: " << body << std::endl;
  std::cout << "FUNC: " << __FUNCTION__ << "  "
            << "query_string: " << query_string << std::endl;

  char n1[100], n2[100];
  char res[100];
  double result;

  /* Get form variables */
  /* string: n1=x&n2=y  */
  if (!body.empty()) {
    struct mg_str http_body;
    http_body.p = body.c_str();
    http_body.len = body.length();
    mg_get_http_var(&http_body, "n1", n1, sizeof(n1));
    mg_get_http_var(&http_body, "n2", n2, sizeof(n2));

  } else if (!query_string.empty()) {
    struct mg_str http_body;
    http_body.p = query_string.c_str();
    http_body.len = query_string.length();
    mg_get_http_var(&http_body, "n1", n1, sizeof(n1));
    mg_get_http_var(&http_body, "n2", n2, sizeof(n2));
  }

  /* Compute the result and send it back as a JSON object */
  result = strtod(n1, NULL) + strtod(n2, NULL);
  sprintf(res, "%0.5f", result);
  reply_callback(c, "200 OK", res);

  return true;
}

int main() {
  std::string port = "7999";
  auto http_server = std::make_shared<HttpServer>();
  http_server->Init(port);
  // add handler
  http_server->AddHandler("/api/fun1", handle_fun1);
  http_server->AddHandler("/api/fun2", handle_fun2);
  http_server->Start();

  return 0;
}

