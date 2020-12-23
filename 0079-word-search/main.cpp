/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/23
 ***********************************/
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {

  int direct[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

  vector<vector<bool>> visited;

  bool checkPoint(int x, int y, int row, int col) {
    if (x >= 0 && x < row && y >= 0 && y < col)
      return true;
    return false;
  }

  // 从board[startX][startY]处开始搜索单词word[index]处开始
  bool dfs(vector<vector<char>>& board, string &word, int startX, int startY, int index) {

    // 检测倒数第一个元素
    if (index == word.size() - 1) {
      return word[index] == board[startX][startY];
    }
#if 1
    if (board[startX][startY] != word[index]) {
      return false;
    }

    // 检测倒数第二个元素
    visited[startX][startY] = true;
    // 保证还有机会进行下一次选择
    for (int i = 0; i < 4; ++i) {
      int newStartX = startX + direct[i][0];
      int newStartY = startY + direct[i][1];
      if (checkPoint(newStartX, newStartY, board.size(), board[0].size()) && !visited[newStartX][newStartY]) {
        // 搜索为真找到结果了，返回
        // 搜索为假，继续尝试搜索，不应返回
        if(dfs(board, word, newStartX, newStartY, index + 1))
          return true;
      }
    }
    visited[startX][startY] = false;
    return false;
#else
    if (board[startX][startY] == word[index]) {
      visited[startX][startY] = true;
      for (int i = 0; i < 4; ++i) {
        int newStartX = startX + direct[i][0];
        int newStartY = startY + direct[i][1];
        if (checkPoint(newStartX, newStartY, board.size(), board[0].size()) && !visited[newStartX][newStartY]) {
          // 搜索为真找到结果了，返回
          // 搜索为假，继续尝试搜索，不应返回
          if(dfs(board, word, newStartX, newStartY, index + 1))
            return true;
        }
      }
      visited[startX][startY] = false;
    }
    return false;
#endif
  }
public:
  bool exist(vector<vector<char>>& board, string word) {
    if (word.size() == 0)
      return false;
    int m = board.size();
    assert(m > 0);
    visited.clear();
    visited = vector<vector<bool>>(board.size(), vector<bool>(board[0].size(), false));
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[0].size(); ++j) {
          if (dfs(board, word, i, j, 0))
            return true;
      }
    }
    return false;
  }
};

int main() {
  vector<vector<char>> board = {
      {'A','B','C','E'},
      {'S','F','C','S'},
      {'A','D','E','E'}};
  vector<vector<char>> board2 = {{'a'}};
    std::cout << Solution().exist(board2, "a") << std::endl;
  std::cout << Solution().exist(board, "ABCCED") << std::endl;
  std::cout << Solution().exist(board, "SEE") << std::endl;
  std::cout << Solution().exist(board, "ABCB") << std::endl;

  return 0;
}

/**
 board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

给定 word = "ABCCED", 返回 true
给定 word = "SEE", 返回 true
给定 word = "ABCB", 返回 false
*/