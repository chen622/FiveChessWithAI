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
#include "basic_chess.h"

namespace ccm {

BasicChess::BasicChess(uint16_t width) : width(width), step_count(0) {
  chessboard = new BoardIndex *[width];
  for (uint16_t i = 0; i < width; ++i) {
    chessboard[i] = new BoardIndex[width];
    for (uint16_t j = 0; j < width; ++j) {
      if (i == width - 1) {
        if (j == 0)
          chessboard[i][j] = BoardIndex::LEFT_TOP;
        else if (j == width - 1)
          chessboard[i][j] = BoardIndex::RIGHT_TOP;
        else
          chessboard[i][j] = BoardIndex::TOP;
      } else if (i == 0) {
        if (j == 0)
          chessboard[i][j] = BoardIndex::LEFT_BOTTOM;
        else if (j == width - 1)
          chessboard[i][j] = BoardIndex::RIGHT_BOTTOM;
        else
          chessboard[i][j] = BoardIndex::BOTTOM;
      } else if (j == 0) {
        chessboard[i][j] = BoardIndex::LEFT;
      } else if (j == width - 1) {
        chessboard[i][j] = BoardIndex::RIGHT;
      } else {
        chessboard[i][j] = BoardIndex::CENTER;
      }
    }
  }
}

BasicChess::BasicChess(const BasicChess &other_chess)
    : width(other_chess.GetWidth()), step_count(other_chess.GetStepCount()) {
  for (const auto &other_step : other_chess.GetFullStep()) {
    full_step.push_back(other_step);
  }

  chessboard = new BoardIndex *[width];

  const auto &board = other_chess.GetChessboard();
  for (uint16_t i = 0; i < width; ++i) {
    chessboard[i] = new BoardIndex[width];
    for (int j = 0; j < width; ++j) {
      this->chessboard[i][j] = board[i][j];
    }
  }
}
uint16_t BasicChess::GetWidth() const {
  return width;
}
BoardIndex **BasicChess::GetChessboard() const {
  return chessboard;
}
uint32_t BasicChess::GetStepCount() const {
  return step_count;
}

const std::vector<std::pair<uint16_t, uint16_t>> &BasicChess::GetFullStep() const {
  return full_step;
}

void BasicChess::PrintBoard() const {
  const auto &last = this->full_step.empty() ? std::pair<uint16_t, uint16_t>(-1, -1) : this->full_step.back();
  for (int16_t i = width - 1; i >= 0; --i) {
    for (int16_t j = 0; j < width; ++j) {
      if (i == last.first && j == last.second) {
        FormatPrint(BoardIndex(1 + static_cast<int>(chessboard[i][j])), i, j);
      } else {
        FormatPrint(chessboard[i][j], i, j);
      }
    }
    std::cout << std::endl;
  }
  std::cout << "\t     ";
  for (uint16_t i = 0; i < width; ++i) {
    std::cout << char(i + 65) << " ";
  }
  std::cout << std::endl;
}

void BasicChess::FormatPrint(BoardIndex type, uint16_t row, uint16_t column) {
  if (column == 0) {
    uint16_t row_number = row + 1;
    std::cout << "\t" << ((row_number < 10) ?
                          "0" + std::to_string(row_number) : std::to_string(row_number));
  }
  switch (type) {
    case BoardIndex::CENTER:std::cout << "╋";
      break;
    case BoardIndex::LEFT_TOP:std::cout << "┏";
      break;
    case BoardIndex::RIGHT_TOP:std::cout << "┓";
      break;
    case BoardIndex::RIGHT_BOTTOM:std::cout << "┛";
      break;
    case BoardIndex::LEFT_BOTTOM:std::cout << "┗";
      break;
    case BoardIndex::TOP:std::cout << "┳";
      break;
    case BoardIndex::RIGHT:std::cout << "┫";
      break;
    case BoardIndex::BOTTOM:std::cout << "┻";
      break;
    case BoardIndex::LEFT:std::cout << "┣";
      break;
    case BoardIndex::BLACK_CHESS:std::cout << "●";
      break;
    case BoardIndex::LAST_BLACK :std::cout << "▲";
      break;
    case BoardIndex::WHITE_CHESS:std::cout << "○";
      break;
    case BoardIndex::LAST_WHITE:std::cout << "△";
      break;
    default:std::cout << "0";
  }
}

int BasicChess::NextStep(std::pair<uint16_t, uint16_t> position) {
//  position.first = width - position.first - 1;
  chessboard[position.first][position.second] =
      this->step_count % 2 == 0 ? BoardIndex::BLACK_CHESS : BoardIndex::WHITE_CHESS;
  this->step_count++;
  this->full_step.push_back(position);
  system("clear");
//  system("CLS");
  this->PrintBoard();
  return HasWin();
}

int BasicChess::HasWin() {
  if (this->step_count < 9) {  // no enough chess to win
    return false;
  }
  BoardIndex compare_val;
  if (this->step_count % 2 == 0) {  // second
    compare_val = BoardIndex::WHITE_CHESS;
  } else {  // first
    compare_val = BoardIndex::BLACK_CHESS;
  }
  const auto &last_step = this->full_step.back();
//  int count = 1;

  // horizontal
  if (this->Traverse(last_step, compare_val, 0, 1) >=5) return 1;

  // vertical
  if (this->Traverse(last_step, compare_val, 1, 0)>=5) return 2;

  // left bottom to right top
  if (this->Traverse(last_step, compare_val, 1, 1)>=5) return 3;

  // right bottom to left top
  if (this->Traverse(last_step, compare_val, 1, -1)>=5) return 4;

  return false;
}

int BasicChess::Traverse(std::pair<uint16_t, uint16_t> last_step, BoardIndex compare_val, int x_para, int y_para) {
  int count = 1;
  for (uint16_t i = 1;; i++) {
    uint16_t x = last_step.first + (i * x_para), y = last_step.second + (i * y_para);
    if (x >= width || y >= width) break;
    if (chessboard[x][y] != compare_val) break;
    count++;
  }

  for (uint16_t i = 1; true; i++) {
    uint16_t x = last_step.first - (i * x_para), y = last_step.second - (i * y_para);
    if (x < 0 || y < 0) break;
    if (chessboard[x][y] != compare_val) break;
    count++;
  }
  return count;
}

bool BasicChess::HasPieceOnPosition(std::pair<uint16_t, uint16_t> position) {
  if (static_cast<int>(this->chessboard[position.first][position.second]) >= 20) {
    return true;
  }
  return false;
}
bool BasicChess::IsForbidden(std::pair<uint16_t,uint16_t> position) {
  return false;
}

}  // namespace ccm
