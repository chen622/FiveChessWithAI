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
#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <cstdint>
#include <utility>
#include <iostream>
#include <cctype>
#include <limits>

namespace ccm {
class Player {
 private:
  int score;  // 分数
  bool is_computer;  // 是否为电脑
  bool is_first;  // 是否为先手
 public:
  int GetScore() const;
  void AddScore(int score);
  bool IsComputer() const;
  void SetIsComputer(bool is_computer);
  bool IsFirst() const;
  void SetIsFirst(bool is_first);
  explicit Player(bool is_first);
  Player(bool is_computer, bool is_first, uint16_t score);

  int Compare(const Player &) const;

  std::pair<int16_t,int16_t> NextStep(int) const;
};
}  // namespace ccm

#endif  // SRC_PLAYER_H_
