/*
  Copyright (c) 2020 Chenming C (ccm@ccm.ink)
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include "src/player.h"

namespace ccm {

uint8_t Player::GetScore() const {
  return score;
}
void Player::SetScore(uint8_t _score) {
  Player::score = _score;
}
bool Player::IsComputer() const {
  return is_computer;
}
void Player::SetIsComputer(bool _is_computer) {
  Player::is_computer = _is_computer;
}
bool Player::IsFirst() const {
  return is_first;
}
void Player::SetIsFirst(bool _is_first) {
  Player::is_first = _is_first;
}
Player::Player(bool is_first) : score(0), is_computer(is_first), is_first(false) {}
Player::Player(bool is_computer, bool is_first, uint8_t score)
    : score(score), is_computer(is_computer), is_first(is_first) {}
}  // namespace ccm
