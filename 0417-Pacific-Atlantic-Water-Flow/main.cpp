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

    bool isMaxLeft(vector<vector<int>>& matrix,int row, int col) {
        int cur = matrix[row][col];
        for (int i = 0; i < col; ++i) {
            if (cur < matrix[row][i])
                return false;
            if (cur == matrix[row][i]) {
                for (int j = i; j < col; ++j) {
                    if (matrix[row][j] != cur)
                        return false;
                }
            }
        }
        return true;
    }

    bool isMaxRight(vector<vector<int>>& matrix, int row, int col) {
        int cur = matrix[row][col];
        for (int i = n-1; i > col; --i) {
            if (cur < matrix[row][i])
                return false;
            if (cur == matrix[row][i]) {
                for (int j = i; j > col; --j) {
                    if (cur != matrix[row][j])
                        return false;
                }
            }
        }
        return true;
    }

    bool isMaxUp(vector<vector<int>>& matrix,int row, int col) {
        int cur = matrix[row][col];
        for (int i = 0; i < row; ++i) {
            if (cur < matrix[i][col])
                return false;
            if (cur == matrix[i][col]) {
                for (int  j = i; j < row; ++j) {
                    if (cur != matrix[j][col])
                        return false;
                }
            }
        }
        return true;
    }

    bool isMaxDown(vector<vector<int>>& matrix, int row, int col) {
        int cur = matrix[row][col];
        for (int i = m-1; i > row; --i) {
            if (cur < matrix[i][col])
                return false;

            if (cur == matrix[i][col]) {
                for (int j = i; j > row; --j) {
                    if (matrix[j][col] != cur)
                        return false;
                }
            }
        }
        return true;
    }

    bool isMax(vector<vector<int>>& matrix, int row, int col) {
        if (isMaxLeft(matrix, row, col) && isMaxDown(matrix,  row, col))
            return true;

        if (isMaxLeft(matrix, row, col) && isMaxRight(matrix, row, col))
            return true;

        if (isMaxUp(matrix, row, col) && isMaxRight(matrix,  row, col))
            return true;

        if (isMaxUp(matrix, row, col) && isMaxDown(matrix,  row, col))
            return true;

        return false;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int>> res;
        m = matrix.size();
        if (m == 0)
            return res;
        n = matrix[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(isMax(matrix, i, j)) {
                    vector<int> a = {i, j};
                    res.push_back(a);
                }
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> matrix = {
            {1,2,3},
            {8,9,4},
            {7,6,5}
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