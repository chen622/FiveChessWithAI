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

#include <iostream>
#include <string>
#include <cstdint>
#include <utility>
#include <vector>

namespace ccm {

// The enum class to record the index of each board type.
enum class BoardIndex{
  CENTER = 0,
  LEFT_TOP = 1,
  RIGHT_TOP = 2,
  RIGHT_BOTTOM = 3,
  LEFT_BOTTOM = 4,
  TOP = 11,
  RIGHT = 12,
  BOTTOM = 13,
  LEFT = 14,
  BLACK_CHESS = 20,
  LAST_BLACK = 21,
  WHITE_CHESS = 30,
  LAST_WHITE = 31
};

class BasicChess {
 private:
  uint16_t width;
  BoardIndex **chessboard;
  // The step has already happened
  uint32_t step_count;
  // The position of each step
  std::vector<std::pair<uint16_t,uint16_t>> full_step;
  // Print the position symbol by type index.
  static void FormatPrint(BoardIndex type, uint16_t row, uint16_t column) ;
  // Return positive if player1 win the match, 0 if no one has already win.
  int HasWin();
  // A template function to traverse positions nearby the last step.
  int Traverse(std::pair<uint16_t, uint16_t> last_step, BoardIndex compare_val, int x_para, int y_para);
 public:
  explicit BasicChess(uint16_t width);
  BasicChess(const BasicChess &);
  uint16_t GetWidth() const;
  BoardIndex **GetChessboard() const;
  uint32_t GetStepCount() const;
  const std::vector<std::pair<uint16_t, uint16_t>> &GetFullStep() const;

  // Print the board in the console.
  void PrintBoard() const;
  // Set a piece into the board.
  int NextStep(std::pair<uint16_t,uint16_t> position);
  // Check the position has piece or not?
  bool HasPieceOnPosition(std::pair<uint16_t,uint16_t> position);
  bool IsForbidden(std::pair<uint16_t,uint16_t> position);
};
}  // namespace ccm

#endif  // SRC_BASIC_CHESS_H_
