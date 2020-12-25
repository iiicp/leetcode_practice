/***********************************
* File:     main.cpp.c
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
    int row, col;
    vector<vector<int>> memo;
    bool inArea(int x, int y) {
        return x >= 0 && x < row && y >= 0 && y < col;
    }

    /// 递归版本
    int tryStart(vector<vector<int>>& grid, int x, int y) {
        /// 未达到终点的路径，不作参考
        if (!inArea(x, y))
            return INT_MAX;

        /// 到达终点
        if (x == row - 1 && y == col - 1) {
            return grid[x][y];
        }

        /// 递归
        return grid[x][y] + std::min(tryStart(grid, x + 1, y),
                                     tryStart(grid, x, y + 1));
    }

    /// 记忆化搜索版本
    int tryStart_memo(vector<vector<int>>& grid, int x, int y) {
        if (!inArea(x, y))
            return INT_MAX;
        /// 到达终点
        if (x == row - 1 && y == col - 1) {
            return grid[x][y];
        }

        int a = 0, b = 0;
        if (inArea(x + 1, y)) {
            if (memo[x+1][y] != -1) {
                a = memo[x+1][y];
            }else {
                a = tryStart_memo(grid, x + 1, y);
                memo[x+1][y] = a;
            }
        }else {
            a = INT_MAX;
        }

        if (inArea(x, y+1)) {
            if (memo[x][y+1] != -1) {
                b = memo[x][y+1];
            }else {
                b = tryStart_memo(grid, x, y+1);
                memo[x][y+1] = b;
            }
        }else {
            b = INT_MAX;
        }

        return grid[x][y] + std::min(a, b);
    }

    /// 动态规划版本
    int tryStart_program(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid);
        for (int i = row - 1; i >= 0 ; --i) {
            for (int j = col - 1; j >= 0; --j) {

                if (i == row - 1 && j == col - 1) {
                    dp[i][j] = grid[i][j];
                }else {
                    int x1 = i + 1, y1 = j;
                    int x2 = i, y2 = j + 1;
                    int a =  i + 1 < row? dp[x1][y1] : INT_MAX;
                    int b =  j + 1 < col? dp[x2][y2] : INT_MAX;
                    dp[i][j] = std::min(a, b) + grid[i][j];
                }
            }
        }

//        for (auto &v : dp) {
//            for (auto n : v) {
//                std::cout << n << " ";
//            }
//            std::cout << std::endl;
//        }

        return dp[0][0];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        row = grid.size();
        if (row == 0)
            return 0;
        col = grid[0].size();
        return tryStart(grid, 0, 0);
    }

    int minPathSum_memo(vector<vector<int>>& grid) {
        row = grid.size();
        if (row == 0)
            return 0;
        col = grid[0].size();
        memo = vector<vector<int>>(row, vector<int>(col, -1));
        return tryStart_memo(grid, 0, 0);
    }

    int minPathSum_program(vector<vector<int>>& grid) {
        row = grid.size();
        if (row == 0)
            return 0;
        col = grid[0].size();
        return tryStart_program(grid);
    }
};

int main() {

    vector<vector<int>> grid{
            {1,3,1},
            {1,5,1},
            {4,2,1}
    };

    clock_t start = clock();
    int res = Solution().minPathSum(grid);
    clock_t end = clock();
    std::cout << "sum: " << res << std::endl;
    std::cout << "time: " << (double)(end- start)/1000 << "ms" << std::endl;


    start = clock();
    res = Solution().minPathSum_memo(grid);
    end = clock();
    std::cout << "sum: " << res << std::endl;
    std::cout << "time: " << (double)(end- start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().minPathSum_program(grid);
    end = clock();
    std::cout << "sum: " << res << std::endl;
    std::cout << "time: " << (double)(end- start)/1000 << "ms" << std::endl;
    return 0;
}