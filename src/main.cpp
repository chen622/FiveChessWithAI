/*
 * MIT License
 *
 * Copyright (c) $YEAR Chenming C (ccm@ccm.ink)
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
#include <iostream>
//#include "basic_chess.h"
#include "src/chess_game.h"

#define TOTAL_MATCH 5

using namespace ccm;
using namespace std;

int main() {
  cout << "欢迎体验Chenming的五子棋！" << endl;
  cout << "请首先选择游戏模式：\n\t0：人人对战\t1：人机对战" << endl;
  int type = 0;
  do {
    cin.clear();
    cout << "请输入您的选择：";
    cin >> type;
    if (cin.fail() || (type != 0) && type != 1) cout << "输入异常，请重新输入！" << endl;
  } while (cin.fail());

  if (type) {
    cout << "not finish!" << endl;
  } else {
    ChessGame game(type, false, TOTAL_MATCH);
    game.Playing();
  }
  return 0;
}
