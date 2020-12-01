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

#define BOARD_SIZE 15  // The size of the board
#define POS_PAIR std::pair<int16_t,int16_t>

namespace ccm {

// The enum class to record the index of each board type.
enum class BoardIndex {
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
  int16_t width;
  BoardIndex **chessboard;
  // The step has already happened
  uint32_t step_count;
  // The position of each step
  std::vector<POS_PAIR> full_step;
  // Print the position symbol by type index.
  static void FormatPrint(BoardIndex type, int16_t row, int16_t column);
  // A template function to traverse positions nearby the last step.
  // Para(0,1): vertical; Para(1,0): horizontal; Para(1,1): left bottom to right top
  int Traverse(POS_PAIR last_step, BoardIndex compare_val, int x_para, int y_para);
  // Check is overline(more than or equal 6) happen or not.
  bool IsOverLine(POS_PAIR position);
  // Check is the count of four more than or equal 2.
  bool IsDoubleFour(POS_PAIR position);
  // Fill in a four and check has five or not.
  // Param see function Traverse()
  bool FillInFourAndCheckFive(POS_PAIR position, int x_para, int y_para);
  // Check is the count of three more than or equal 2.
  bool IsDoubleThree(POS_PAIR position);
  // Fill in a three and check has four or not.
  // Param see function Traverse()
  bool FillInThreeAndCheckFour(POS_PAIR position, int x_para, int y_para);
 public:
  explicit BasicChess(int16_t width);
  BasicChess(const BasicChess &);
  int16_t GetWidth() const;
  BoardIndex **GetChessboard() const;
  uint32_t GetStepCount() const;

  // Return positive if player1 win the match, 0 if no one has already win.
  int HasWin();
  const std::vector<POS_PAIR> &GetFullStep() const;
  // Print the board in the console.
  void PrintBoard() const;
  // Set a piece into the board.
  int NextStep(POS_PAIR position,bool silently);
  // Check the position has piece or not?
  bool HasPieceOnPosition(POS_PAIR position);
  bool IsForbidden(POS_PAIR position);
};
}  // namespace ccm

#endif  // SRC_BASIC_CHESS_H_
