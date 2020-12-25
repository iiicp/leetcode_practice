/**********************************
 * File:     main.cpp
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/25
 ***********************************/

#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

class Solution {
//  vector<vector<bool>> used;

  // 对于递归的退出条件认识不深
//  void findSudoku(vector<vector<char>>& board, int row, int col) {
//    std::cout << "row = " << row << "col = " << col << std::endl;
//    if (row == board.size() && col >= 0)
//      return;
//
//
//    if (col < board.size()) {
//      int l = col;
//      while (l < board.size()) {
//        if (board[row][l] == '.') {
//          for (int c = '1'; c <= '9'; ++c) {
//            if (canSelect(board, row, col, c)) {
//              board[row][col] = c;
//              findSudoku(board, row, l + 1);
//              board[row][col] = '.';
//            }
//          }
//        }
//        l++;
//      }
//      if (l == board.size()) {
//        findSudoku(board, row + 1, 0);
//      }
//    }
//  }

  vector<vector<bool>> rowUsed;
  vector<vector<bool>> colUsed;
  vector<vector<bool>> blockUsed;

  /**
   *  可能的bug
   *  1, 字符'0'~'9'和数字0~9的bug，要处理的是字符，就要按照字符的方式来处理判断
   *  2, 此题是有唯一解，所以此题设计成返回bool的递归，可以进行快速退出，避免回溯
   *  3, 此题回溯递归的深度是将二维布局，一维化，设置一个pos index，这样pos的深度永远是递增的，就一定能够退出
   *  4, 此题求坐标需要一点点数学技巧吧，一般通过pos来求坐标就是 除和模，还有统计block Index的使用，在面试中要沉住气
   */
  bool dfs(vector<vector<char>>& board, int pos) {
    if (pos == 81)
      return true;

    int r = pos / 9;
    int c = pos % 9;

    /// 剪枝，减少内存的开销
    int nextPos = pos + 1;
    while (nextPos < 81) {
      if (board[nextPos/9][nextPos%9] == '.')
        break;
      nextPos++;
    }
//    if (board[r][c] != '.')
//      return dfs(board, pos + 1);

    for (int i = 1; i <= 9; ++i) {
      int blockIndex = r/3*3+c/3;
      if (!rowUsed[r][i] && !colUsed[c][i] &&
          !blockUsed[blockIndex][i]) {
        rowUsed[r][i] = true;
        colUsed[c][i] = true;
        blockUsed[blockIndex][i] = true;
        board[r][c] = i + '0'; // 注意此处往棋盘中添加的是字符'0'~'9'
        if(dfs(board, nextPos)){
          return true; // 找到了，不进行回溯了，直接返回；递归返回值就是
        }
        // 否则继续回溯
        board[r][c] = '.';
        rowUsed[r][i] = false;
        colUsed[c][i] = false;
        blockUsed[blockIndex][i] = false;
      }
    }
    // 没有找到，继续回溯
    return false;
  }
public:
  void solveSudoku(vector<vector<char>>& board) {

    rowUsed = vector<vector<bool>>(9, vector<bool>(10, false));
    colUsed = vector<vector<bool>>(9, vector<bool>(10, false));
    blockUsed = vector<vector<bool>>(9, vector<bool>(10, false));

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] != '.') {
          rowUsed[i][board[i][j] - '0'] = true;
          colUsed[j][board[i][j] - '0'] = true;
          blockUsed[i/3*3+j/3][board[i][j] - '0'] = true;
        }
      }
    }

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          assert(dfs(board, i * 9 + j));
          return;
        }
      }
    }
  }
};

int main() {

  vector<vector<char>> sudoku = {
      {'5','3','.', '.','7','.', '.','.','.' },
      {'6','.','.', '1','9','5', '.','.','.' },
      {'.','9','8', '.','.','.', '.','6','.' },
      {'8','.','.', '.','6','.', '.','.','3' },
      {'4','.','.', '8','.','3', '.','.','1' },
      {'7','.','.', '.','2','.', '.','.','6' },
      {'.','6','.', '.','.','.', '2','8','.' },
      {'.','.','.', '4','1','9', '.','.','5' },
      {'.','.','.', '.','8','.', '.','7','9' },
  };

  for (int i = 0; i < sudoku.size(); ++i) {
    for (int j = 0; j < sudoku.size(); ++j) {
      std::cout << sudoku[i][j] << ", ";
    }
    std::cout << std::endl;
  }

  clock_t start = clock();
  Solution().solveSudoku(sudoku);
  clock_t end = clock();

  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  std::cout << std::endl;

  for (int i = 0; i < sudoku.size(); ++i) {
    for (int j = 0; j < sudoku.size(); ++j) {
      std::cout << sudoku[i][j] << ", ";
    }
    std::cout << std::endl;
  }

  return 0;
}
