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
#include "tree_node.h"
namespace ccm {
char GetCharOfPosition(BoardIndex index, BoardIndex my, BoardIndex rival);

TreeNode::TreeNode(bool is_black, const BasicChess &basic_chess)
    : depth(0), type(true), is_black(is_black), basic_chess(basic_chess) {
}
TreeNode::TreeNode(const TreeNode &last_node, std::pair<int16_t, int16_t> position)
    : depth(0), type(true), is_black(!last_node.is_black), basic_chess(last_node.basic_chess) {
  this->basic_chess.NextStep(position);
  int a = this->UpdateScore(position);
  std::cout<<a;
}
int TreeNode::UpdateScore(std::pair<int16_t, int16_t> position) {
  std::string my_lines[4];
  std::string rival_lines[4];
  BoardIndex my_index = this->is_black ? BoardIndex::BLACK_CHESS : BoardIndex::WHITE_CHESS;
  BoardIndex rival_index = this->is_black ? BoardIndex::WHITE_CHESS : BoardIndex::BLACK_CHESS;
  const auto &board = this->basic_chess.GetChessboard();

  // -
  for (int i = 0; i < BOARD_SIZE; i++) {
    my_lines[0].push_back(GetCharOfPosition(board[position.second][i], my_index, rival_index));
    rival_lines[0].push_back(GetCharOfPosition(board[position.second][i], rival_index, my_index));
  }

  // |
  for (int i = 0; i < BOARD_SIZE; i++) {
    my_lines[1].push_back(GetCharOfPosition(board[i][position.second], my_index, rival_index));
    rival_lines[1].push_back(GetCharOfPosition(board[i][position.second], rival_index, my_index));
  }

  // \/
  for (int i = position.first - std::min(position.first, position.second),
           j = position.second - std::min(position.first, position.second); i < BOARD_SIZE && j < BOARD_SIZE;
       i++, j++) {
    my_lines[2].push_back(GetCharOfPosition(board[i][position.second], my_index, rival_index));
    rival_lines[2].push_back(GetCharOfPosition(board[i][position.second], rival_index, my_index));
  }

  // /
  for (int i = position.first + std::min((int) position.second, BOARD_SIZE - position.first - 1),
           j = position.second - std::min(BOARD_SIZE - position.first - 1, (int) position.second);
       i >= 0 && j < BOARD_SIZE;
       i--, j++) {
    my_lines[3].push_back(GetCharOfPosition(board[i][position.second], my_index, rival_index));
    rival_lines[3].push_back(GetCharOfPosition(board[i][position.second], rival_index, my_index));
  }

  int my_line_scores[4]{0};
  int rival_line_scores[4]{0};

  for (int i = 0; i < 4; ++i) {
    for (const auto &pattern: patterns) {
      if (my_lines[i].find(pattern.pattern)) {
        my_line_scores[i] += pattern.score;
      }
      if (rival_lines[i].find(pattern.pattern)) {
        rival_line_scores[i] += pattern.score;
      }
    }
  }

  int16_t a = position.first;
  int16_t b = BOARD_SIZE + position.second;
  int16_t c = 2 * BOARD_SIZE + (position.second - position.first + BOARD_SIZE - 1);
  int16_t d = 2 * BOARD_SIZE + BOARD_SIZE * 2 - 1 + (position.first + position.second);

  int old_score = total_score[0] - total_score[1];
  for (int i = 0; i < 2; ++i) {
    total_score[i] -= line_score[i][a] + line_score[i][b] + line_score[i][c] + line_score[i][d];
  }
  line_score[0][a] = my_line_scores[0];
  line_score[1][a] = rival_line_scores[0];
  line_score[0][b] = my_line_scores[1];
  line_score[1][b] = rival_line_scores[1];
  line_score[0][c] = my_line_scores[2];
  line_score[1][c] = rival_line_scores[2];
  line_score[0][d] = my_line_scores[3];
  line_score[1][d] = rival_line_scores[3];

  for (int i = 0; i < 2; ++i) {
    total_score[i] += line_score[i][a] + line_score[i][b] + line_score[i][c] + line_score[i][d];
  }
  return total_score[0] - total_score[1] - old_score;
}

char GetCharOfPosition(BoardIndex index, BoardIndex my, BoardIndex rival) {
  return index == my ? '1' : index == rival ? '2' : '0';
}

}
