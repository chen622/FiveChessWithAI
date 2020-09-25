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
#ifndef SRC_CHESS_GAME_H_
#define SRC_CHESS_GAME_H_
#include <cstdint>
#include <vector>
#include "src/player.h"
#include "src/basic_chess.h"

#define BOARD_SIZE 15  // The size of the board

namespace ccm {
// A Class used to managing a chess game.
// Example:
//    ChessGame game(true, true, 5);
//    int ret = game.Playing();
class ChessGame {
 private:
  // The count of matches already finished
  uint8_t count;
  // The count of matches which need to finish
  uint8_t total_count;
  Player player1;
  Player player2;
  // A vector to save all chess boards
  vector<BasicChess> boards;
  // Function to start a match.
  // Return positive if player1 win a match, 0 if no one win.
  int PlayAMatch();
  // Return positive if player1 win the game, 0 if no one has already win.
  int WhoWinGame();

 public:
  ChessGame(bool has_computer, bool computer_first, uint8_t total_count);
  int Playing();
};
}  // namespace ccm
#endif  // SRC_CHESS_GAME_H_
