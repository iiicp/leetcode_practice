/***********************************
* File:     main.cpp.c
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/24
***********************************/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
    int m, n;
    vector<vector<bool>> visitPacific;
    vector<vector<bool>> visitAtlantic;
    int direc[4][2] = {{-1,0}, {0, 1}, {1, 0}, {0, -1}};
    bool inAear(int i, int j) {
      return i >= 0 && i < m && j >= 0 && j < n;
    }
    void search(vector<vector<int>>& matrix, int i, int j, vector<vector<bool>>& visited, int preValue) {
        visited[i][j] = true;
        for (int k = 0; k < 4; ++k) {
          int newX = i + direc[k][0];
          int newY = j + direc[k][1];
          if (inAear(newX, newY) && matrix[newX][newY] >= matrix[i][j] && !visited[newX][newY]) {
            search(matrix, newX, newY, visited, matrix[i][j]);
          }
      }
    }
public:
    /// 从边缘的点去探索
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int>> res;
        m = matrix.size();
        if (m == 0)
            return res;
        n = matrix[0].size();

        visitAtlantic = vector<vector<bool>>(m, vector<bool>(n, false));
        visitPacific = visitAtlantic;

        for (int i = 0; i < m; ++i) {
          search(matrix, i, 0, visitPacific, INT_MIN);
          search(matrix, i, n - 1, visitAtlantic,INT_MIN);
        }

        for (int i = 0; i < n; ++i) {
          search(matrix, 0, i, visitPacific,INT_MIN);
          search(matrix, m - 1, i, visitAtlantic,INT_MIN);
        }

        for (int i = 0; i < m; ++i)
          for (int j = 0; j < n; ++j)
            if (visitAtlantic[i][j] == true && visitPacific[i][j] == true)
                res.push_back({i, j});
        return res;
    }
};

int main() {
    vector<vector<int>> matrix = {
        {1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}
    };

    vector<vector<int>> res = Solution().pacificAtlantic(matrix);

    for (auto &v : res) {
        std::cout << "[";
        for (auto n : v) {
            std::cout << n << ", ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}