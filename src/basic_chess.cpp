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
#include "basic_chess.h"

namespace ccm {
    int **BasicChess::get_chessboard() const {
        return chessboard;
    }

    int BasicChess::get_width() const {
        return width;
    }

    void BasicChess::PrintBoard() const {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < width; ++j) {
                FormatPrint(chessboard[i][j]);
            }
            std::cout << std::endl;
        }
    }

    void BasicChess::FormatPrint(int type) {
        switch (type) {
            case 0:
                std::cout << "╋";
                break;
            case 1:
                std::cout << "┏";
                break;
            case 2:
                std::cout << "┓";
                break;
            default:
                std::cout << "0";
        }
    }

    BasicChess::BasicChess(int width) : width(width) {
        chessboard = new int *[width];
        for (int i = 0; i < width; ++i) {
            chessboard[i] = new int[width];
            for (int j = 0; j < width; ++j) {
                chessboard[i][j] = 0;
            }
        }
    }
}
