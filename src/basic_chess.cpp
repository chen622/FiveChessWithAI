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
#include "src/basic_chess.h"

namespace ccm {

BasicChess::BasicChess(uint8_t width) : width(width) {
  chessboard = new int *[width];
  for (uint8_t i = 0; i < width; ++i) {
    chessboard[i] = new int[width];
    for (uint8_t j = 0; j < width; ++j) {
      if (i == 0) {
        if (j == 0)
          chessboard[i][j] = 1;
        else if (j == width - 1)
          chessboard[i][j] = 2;
        else
          chessboard[i][j] = 11;
      } else if (i == width - 1) {
        if (j == 0)
          chessboard[i][j] = 4;
        else if (j == width - 1)
          chessboard[i][j] = 3;
        else
          chessboard[i][j] = 13;
      } else if (j == 0) {
        chessboard[i][j] = 14;
      } else if (j == width - 1) {
        chessboard[i][j] = 12;
      } else {
        chessboard[i][j] = 0;
      }
    }
  }
}

uint8_t BasicChess::GetWidth() const {
  return width;
}
int **BasicChess::GetChessboard() const {
  return chessboard;
}
uint32_t BasicChess::GetCount() const {
  return count;
}
uint32_t BasicChess::AddAfterGet() {
  return count++;
}

void BasicChess::PrintBoard() const {
  for (uint8_t i = 0; i < width; ++i) {
    for (uint8_t j = 0; j < width; ++j) {
      FormatPrint(chessboard[i][j], i, j);
    }
    std::cout << std::endl;
  }
  std::cout << "\t     ";
  for (uint8_t i = 0; i < width; ++i) {
    std::cout << char(i + 65) << " ";
  }
  std::cout << std::endl;
}

void BasicChess::FormatPrint(uint8_t type, uint8_t row, uint8_t column) const {
  uint8_t row_number = (width - row - 1);
  std::string row_mark = (row_number < 10) ?
                         "0" + std::to_string(row_number) : std::to_string(row_number);
  switch (type) {
    case 0:std::cout << "╋";
      break;
    case 1:std::cout << "\t" << row_mark << "┏";
      break;
    case 2:std::cout << "┓";
      break;
    case 3:std::cout << "┛";
      break;
    case 4:std::cout << "\t" << row_mark << "┗";
      break;
    case 11:std::cout << "┳";
      break;
    case 12:std::cout << "┫";
      break;
    case 13:std::cout << "┻";
      break;
    case 14:std::cout << "\t" << row_mark << "┣";
      break;
    case BLACK_CHESS_INDEX:std::cout << "●";
      break;
    case BLACK_CHESS_INDEX + 1:std::cout << "▲";
      break;
    case WHITE_CHESS_INDEX:std::cout << "○";
      break;
    case WHITE_CHESS_INDEX + 1:std::cout << "△";
      break;
    default:std::cout << "0";
  }
}

int BasicChess::NextStep(std::pair<uint8_t,uint8_t> position) {
  return 0;
}
int BasicChess::WhoWinMatch() {
  return 0;
}

}  // namespace ccm
