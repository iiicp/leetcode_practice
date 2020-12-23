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
#include <queue>

using namespace std;

class Solution {
    vector<vector<bool>> visited;
    int m, n;
    int direct[4][2] = {{-1,0}, {0, 1}, {1, 0}, {0, -1}};
    bool inArea(int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    }
    bool isSurrouned = true;

    void dfs(vector<vector<char>>& board, int startX, int startY, vector<pair<int, int>> &record) {

        visited[startX][startY] = true;
        record.push_back(make_pair(startX, startY));

        for (int i = 0; i < 4; ++i) {
            int newX = startX + direct[i][0];
            int newY = startY + direct[i][1];

            if (!inArea(newX, newY)) {
                isSurrouned = false;
                continue;
            }

            if (!visited[newX][newY] && board[newX][newY] == 'O') {
                dfs(board, newX, newY, record);
            }
        }
    }

    void bfs(vector<vector<char>>& board, int startX, int startY, vector<pair<int, int>> &record) {
        queue<pair<int, int>> q;
        q.push(make_pair(startX, startY));
        visited[startX][startY] = true;
        record.push_back(make_pair(startX, startY));

        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int newX = x + direct[i][0];
                int newY = y + direct[i][1];

                if (!inArea(newX, newY)) {
                    isSurrouned = false;
                    continue;
                }

                if (board[newX][newY] == 'O' && !visited[newX][newY]) {
                    q.push(make_pair(newX, newY));
                    visited[newX][newY] = true;
                    record.push_back(make_pair(newX, newY));
                }
            }
        }
    }

public:
  /// 被环绕的O，说明值为O就一定在棋盘上
  /// 这是一个退出的很重要的条件
  void solve(vector<vector<char>>& board) {
    m = board.size();
    assert(m > 0);
    n = board[0].size();
    visited = vector<vector<bool>>(m, vector<bool>(n, false));
    vector<pair<int, int>> record;
      for (int i = 0; i < m; ++i) {
          for (int j = 0; j < n; ++j) {
              if (board[i][j] == 'O' && !visited[i][j]) {
                  record.clear();
                  isSurrouned = true;
                  bfs(board, i, j, record);
                  if (isSurrouned) {
                      for (auto &p : record) {
                          board[p.first][p.second] = 'X';
                      }
                  }
              }
          }
      }
  }
};

int main(){
    vector<vector<char>> board = {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'X', 'X'}
    };

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    Solution().solve(board);

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

  return 0;
}