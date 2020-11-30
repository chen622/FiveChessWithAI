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
  if (is_black) {
    this->possible_positions.emplace_back((BOARD_SIZE - 1) / 2, (BOARD_SIZE - 1) / 2);
  }
}
TreeNode::TreeNode(const TreeNode &last_node, POS_PAIR position)
    : depth(0), type(true), is_black(!last_node.is_black), basic_chess(last_node.basic_chess) {
  this->basic_chess.NextStep(position, true);
  this->UpdateScore(position);
  this->AddPossiblePosition(position);
}
TreeNode::TreeNode(POS_PAIR position, TreeNode *father_node)
    : depth(father_node->depth + 1),
      type(!father_node->type),
      is_black(father_node->is_black),
      basic_chess(father_node->basic_chess),
      alpha(father_node->alpha),
      beta(father_node->beta) {
  this->basic_chess.NextStep(position, true);
  this->UpdateScore(position);
  this->AddPossiblePosition(position);
}

int TreeNode::UpdateScore(POS_PAIR position) {
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
    for (const auto &pattern: patterns_score) {
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

void TreeNode::AddPossiblePosition(POS_PAIR position) {
  const auto &board = this->basic_chess.GetChessboard();
  std::remove(this->possible_positions.begin(), this->possible_positions.end(), position);
  for (int i = 0; i < 8; ++i) {
    POS_PAIR temp_position = POS_PAIR(position);
    for (int j = 0; j < 2; ++j) {
      switch (i) {
        case 0:temp_position.first++;
          break;
        case 1:temp_position.first++;
          temp_position.second++;
          break;
        case 2:temp_position.second++;
          break;
        case 3:temp_position.first--;
          temp_position.second++;
          break;
        case 4:temp_position.first--;
          break;
        case 5:temp_position.first--;
          temp_position.second--;
          break;
        case 6:temp_position.second--;
          break;
        case 7:temp_position.second--;
          temp_position.first++;
          break;
        default:break;
      }
      if (temp_position.first >= 0 && temp_position.first < this->basic_chess.GetWidth()
          && temp_position.second >= 0 && temp_position.second < this->basic_chess.GetWidth()
          && !this->basic_chess.HasPieceOnPosition(temp_position)) {
        this->possible_positions.push_back(temp_position);
      }
    }
  }
}

int TreeNode::ABSearch() {
  int retVal = this->type ? this->alpha : this->beta;
  if (this->depth >= MAX_DEPTH) {
    return this->total_score[0] - this->total_score[1];
  }
  // Random sort the possible position
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(this->possible_positions.begin(), this->possible_positions.end(), std::default_random_engine(seed));

  for (const auto &position: this->possible_positions) {
    TreeNode child_node = TreeNode(position, this);
    int child_score = child_node.ABSearch();
    if (this->type) { // MAX
      if (child_score > this->alpha) {
        this->alpha = child_score;
        retVal = child_score;
      }
    } else { //MIN
      if (child_score < this->beta) {
        this->beta = child_score;
        retVal = child_score;
      }
    }
    if (this->alpha >= this->beta) {
      break;
    } else {
      this->children_nodes.push_back(child_node);
    }
  }
  return retVal;
}
POS_PAIR TreeNode::GetGoodMove() {
  int max_score = this->ABSearch();
  for (const auto &child: children_nodes) {
    if (child.beta == max_score) {
      return child.basic_chess.GetFullStep().back();
    }
  }
  return POS_PAIR(-1, -1);
}

char GetCharOfPosition(BoardIndex index, BoardIndex my, BoardIndex rival) {
  return index == my ? '1' : index == rival ? '2' : '0';
}

}
