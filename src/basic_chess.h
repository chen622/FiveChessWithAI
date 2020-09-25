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
#ifndef SRC_BASIC_CHESS_H_
#define SRC_BASIC_CHESS_H_

// The index value which represent the black chess.
#define BLACK_CHESS_INDEX 50
// The index value which represent the white chess.
#define WHITE_CHESS_INDEX 52
#include <iostream>
#include <string>
#include <cstdint>
#include <utility>

namespace ccm {

class BasicChess {
 private:
  uint8_t width;
  int **chessboard;
  // The step has already happened
  uint32_t count;
  void FormatPrint(uint8_t type, uint8_t row, uint8_t column) const;
  // Return positive if player1 win the match, 0 if no one has already win.
  int WhoWinMatch();
 public:
  uint8_t GetWidth() const;
  int **GetChessboard() const;
  uint32_t GetCount() const;
  uint32_t AddAfterGet();

  // Print the board in the console.
  void PrintBoard() const;
  int NextStep(std::pair<uint8_t,uint8_t> position);
  explicit BasicChess(uint8_t width);
};
}  // namespace ccm

#endif  // SRC_BASIC_CHESS_H_
