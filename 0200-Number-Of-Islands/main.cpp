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
#include <iostream>

using namespace std;

class Solution {
  int direction[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
  int m, n;

  vector<vector<bool>> visited;

  bool inArea(int x, int y) {
    if (x >= 0 && x < m && y >= 0 && y < n)
      return true;
    return false;
  }

  /// 搜索岛屿的过程就是标记的过程，重在标记
  /// 因为搜索岛屿的过程中没有target
  void searchIsland(vector<vector<char>>& grid, int startX, int startY) {
    visited[startX][startY] = true;
    for (int i = 0; i < 4; ++i) {
      int newX = startX + direction[i][0];
      int newY = startY + direction[i][1];
      if (inArea(newX, newY) && grid[newX][newY] == '1' && !visited[newX][newY]) {
        searchIsland(grid, newX, newY);
      }
    }
  }
public:
  int numIslands(vector<vector<char>>& grid) {
    m = grid.size();
    assert(m > 0);
    n = grid[0].size();

    visited = vector<vector<bool>>(m, vector<bool>(n, false));

    /// 主控去统计岛屿的个数
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '1' && !visited[i][j]) {
          // 踩点
          searchIsland(grid, i, j);
          res++;
        }
      }
    }
    return res;
  }
};

/*
输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
 输出：3

  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
 */
int main() {
  vector<vector<char>> islands{
      {'1','1','1','1','0'},
      {'1','1','0','1','0'},
      {'1','1','0','0','0'},
      {'0','0','0','0','0'},
  };
  std::cout << Solution().numIslands(islands) << std::endl;
  return 0;
}