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
#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include "basic_chess.h"
#define MAX_DEPTH 3
#define INFINITY_SCORE 1000000

namespace ccm {

struct Pattern {
  std::string pattern;
  int score;
};

static std::vector<Pattern> patterns_score = {
    {"11111", INFINITY_SCORE / 10},
    {"011110", 6000},
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
  int alpha = -INFINITY_SCORE;
  int beta = INFINITY_SCORE;
  std::vector<TreeNode> children_nodes = {};
  bool is_black; // is first or not
  int line_score[2][BOARD_SIZE * 6 - 2]{0};
  int total_score[2]{0};
  std::vector<POS_PAIR> possible_positions = {};
  BasicChess basic_chess;
  // This constructor is used to create a child node of a decision tree.
  TreeNode(POS_PAIR position, TreeNode *father_node);
  int UpdateScore(POS_PAIR position);
  void AddPossiblePosition(POS_PAIR);
  int ABSearch();
 public:
  TreeNode(bool is_black, const BasicChess &);
  ~TreeNode();
  // This constructor is used to init a decision tree.
  TreeNode(const TreeNode *last_node, POS_PAIR position);
  POS_PAIR GetGoodMove();
  void PrintTree();
};
}

#endif  // SRC_TREE_NODE_H_
