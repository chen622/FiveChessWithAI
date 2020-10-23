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
#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <json/json.h>
#include <http_server.h>
#include "chess_game.h"

std::unordered_map<int, ccm::ChessGame> game_map;
int game_index = 0;

//bool handle_fun1(const Json::Value &body,
//                 const std::string &query_string,
//                 mg_connection *c,
//                 OnRspCallback reply_callback) {
//  std::cout << "FUNC: " << __FUNCTION__ << "  "
//            << "body: " << body << std::endl;
//  std::cout << "FUNC: " << __FUNCTION__ << "  "
//            << "query_string: " << query_string << std::endl;
//
//  reply_callback(c, "200 OK", "success");
//
//  return true;
//}

bool create_game(const Json::Value &body,
                 const std::string &query_string,
                 mg_connection *c,
                 OnRspCallback reply_callback) {
  std::cout << body.toStyledString() << std::endl;
  if (!body.isMember("hasComputer") || !body.isMember("computerFirst")){
    reply_callback
  }
  Json::Value rsp;
  ccm::ChessGame new_game;

  reply_callback(c, 200, rsp);
//  ccm::ChessGame new_game();
  return true;
}

int main() {
  std::string port = "8000";
  auto http_server = std::make_shared<HttpServer>();
  http_server->Init(port);
  // add handler
  http_server->AddHandler("/api/fun1", create_game);
//  http_server->AddHandler("/api/fun2", handle_fun2);
  http_server->Start();

  return 0;
}

