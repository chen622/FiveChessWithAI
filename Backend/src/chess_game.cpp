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
#include "chess_game.h"
namespace ccm {
ChessGame::ChessGame(bool has_computer, bool computer_first, uint16_t total_count)
    : total_count(total_count), player1(true), player2(false), count(0) {
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
  int game_rst = 0;
  while ((game_rst = WhoWinGame()) == 0) {
    int match_rst = this->PlayAMatch();
    if (match_rst > 0){
      this->player1.AddScore(1);
    }else {
      this->player2.AddScore(1);
    }
    this->count++;
  }
  return game_rst;
}

int ChessGame::PlayAMatch() {
  int who_win = 0;
  BasicChess board(BOARD_SIZE);
  TreeNode tree_node = TreeNode(this->count % 2 == 0 ? this->player1.IsComputer() : this->player2.IsComputer(), board);
  board.PrintBoard();
  while (who_win == 0) {  // check match has finish or not
    POS_PAIR position;
    if ((board.GetStepCount()) % 2 == (this->count % 2)) {  // player 1 term
      if (player1.IsComputer()) {
        position = tree_node.GetGoodMove();
      } else {
        while (true) {
          position = player1.NextStep(BOARD_SIZE);
          if (board.HasPieceOnPosition(position)) {
            std::cout << "落子位置已有棋子，请重新输入！" << std::endl;
          } else if (this->count % 2 == 0 && board.IsForbidden(position)) {  // second term has forbidden position
            std::cout << "落子位置为禁手，请重新输入！" << std::endl;
          } else {
            break;
          }
        }
        if (player2.IsComputer()) {
          tree_node = TreeNode(tree_node, position);
        }
      };
      who_win = board.NextStep(position, false);
    } else {  // player 2 term
      if (player2.IsComputer()) {
        position = tree_node.GetGoodMove();
      } else {
        while (true) {
          position = player2.NextStep(BOARD_SIZE);
          if (board.HasPieceOnPosition(position)) {
            std::cout << "落子位置已有棋子，请重新输入！" << std::endl;
          } else if (this->count % 2 == 1 && board.IsForbidden(position)) {  // second term has forbidden position
            std::cout << "落子位置为禁手，请重新输入！" << std::endl;
          } else {
            break;
          }
        }
        if (player2.IsComputer()) {
          tree_node = TreeNode(tree_node, position);
        }
      }
      who_win = -board.NextStep(position,false);
    }
  }
  boards.push_back(board);
  std::cout << "一句比赛结束" << (who_win > 0 ? "玩家1获胜" : "玩家2获胜") << std::endl;
  return who_win;
}

int ChessGame::WhoWinGame() {
  if (this->count >= this->total_count) {
    return this->player1.Compare(this->player2);
  } else {
    return 0;
  }
}

}  // namespace ccm
