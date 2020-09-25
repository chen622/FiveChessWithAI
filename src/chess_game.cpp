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
#include "src/chess_game.h"
namespace ccm {
ChessGame::ChessGame(bool has_computer, bool computer_first, uint8_t total_count)
    : total_count(total_count), player1(true), player2(false) {
  if (has_computer) {  // PVE
    if (computer_first) {
      this->player1.SetIsComputer(true);
    } else {
      this->player2.SetIsComputer(true);
    }
  } else {  // PVP

  }
}

int ChessGame::Playing() {
  while (WhoWinGame() == 0) {

  }
  return 0;
}

int ChessGame::PlayAMatch() {
  int who_win = 0;
  BasicChess board(BOARD_SIZE);
  while (who_win == 0) {
    pair<uint8_t,uint8_t> position;
    if (board.GetCount() % 2 == 0) {
      position = player1.NextStep();

    } else {

    }
    who_win = board.
  }
  boards.push_back(board);
}

int ChessGame::WhoWinGame() {
  if (this->count >= this->total_count) {
    return this->player1.Compare(this->player2);
  } else {
    return 0;
  }
}

}  // namespace ccm
