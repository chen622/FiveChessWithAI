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
#ifndef SRC_TREE_NODE_H_
#define SRC_TREE_NODE_H_
#include "basic_chess.h"
#include "chess_game.h"
#include <algorithm>
#define MAX_DEPTH 3

namespace ccm {

struct Pattern {
  std::string pattern;
  int score;
};

std::vector<Pattern> patterns = {
    {"11111", 50000},
    {"011110", 4320},
    {"011100", 720},
    {"001110", 720},
    {"011010", 720},
    {"010110", 720},
    {"11110", 720},
    {"01111", 720},
    {"11011", 720},
    {"10111", 720},
    {"11101", 720},
    {"001100", 120},
    {"001010", 120},
    {"010100", 120},
    {"000100", 20},
    {"001000", 20},
};

class TreeNode {
 private:
  int depth;
  bool type; // true is max
  bool is_black; // is first or not
  int line_score[2][BOARD_SIZE * 6 - 2]{0};
  int total_score[2]{0};
  BasicChess basic_chess;
 public:
  TreeNode(bool is_black, const BasicChess &);
  TreeNode(const TreeNode &last_node, std::pair<int16_t, int16_t> position);
  int UpdateScore(std::pair<int16_t, int16_t> position);
};
}

#endif  // SRC_TREE_NODE_H_
