/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/27
***********************************/

#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

/**
 * !!!!!
 *      注意起点和终点为障碍物的情况
 */

class Solution {
    int tryStart_dfs(vector<vector<int>>& obstacleGrid, int x, int y) {
        /// 如果起点为障碍物
        if (obstacleGrid[0][0] == 1)
            return 0;

        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (x == m - 1 && y == n - 1) {
            /// 考虑了终点为障碍物的情况
            return obstacleGrid[m-1][n-1] == 1 ? 0 : 1;
        }

        int res = 0;
        if (x + 1 < m && obstacleGrid[x + 1][y] == 0) {
            res += tryStart_dfs(obstacleGrid, x + 1, y);
        }
        if (y + 1 < n && obstacleGrid[x][y+1] == 0) {
            res += tryStart_dfs(obstacleGrid, x, y + 1);
        }
        return res;
    }

    vector<vector<long>> memo;
    int tryStart_memo(vector<vector<int>>& obstacleGrid, int x, int y) {
        /// 如果起点为障碍物
        if (obstacleGrid[0][0] == 1)
            return 0;

        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (x == m - 1 && y == n - 1) {
            return obstacleGrid[m-1][n-1] == 1 ? 0 : 1;
        }

        if (memo[x][y] != -1)
            return memo[x][y];

        int res = 0;
        if (x + 1 < m && obstacleGrid[x + 1][y] == 0) {
            res += tryStart_memo(obstacleGrid, x + 1, y);
        }
        if (y + 1 < n && obstacleGrid[x][y+1] == 0) {
            res += tryStart_memo(obstacleGrid, x, y + 1);
        }
        memo[x][y] = res;
        return res;
    }

    long tryStart_dp(vector<vector<int>>& obstacleGrid) {
        /// 如果起点为障碍物
        if (obstacleGrid[0][0] == 1)
            return 0;

        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<long>> dp(m, vector<long>(n, 0));
        /// 判断终点是否为1的情况
        dp[m-1][n-1] = obstacleGrid[m-1][n-1] == 1 ? 0 : 1;

        for (int i = m-1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i == m-1 && j == n-1)
                    continue;
                long  a = (i+1) < m && obstacleGrid[i+1][j] == 0 ? dp[i+1][j] : 0;
                long  b = (j+1) < n && obstacleGrid[i][j+1] == 0 ? dp[i][j+1] : 0;
                dp[i][j] = a + b;
            }
        }
        return dp[0][0];
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return tryStart_dfs(obstacleGrid, 0, 0);
    }

    int uniquePathsWithObstacles_memo(vector<vector<int>>& obstacleGrid) {
        memo = vector<vector<long>>(obstacleGrid.size(), vector<long>(obstacleGrid[0].size(), -1));
        return tryStart_memo(obstacleGrid, 0, 0);
    }

    int uniquePathsWithObstacles_dp(vector<vector<int>>& obstacleGrid) {
        return tryStart_dp(obstacleGrid);
    }
};

int main() {
#if 0
    srand(time(NULL));
    vector<vector<int>> grid(24, vector<int>(26, 0));
    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 26; ++j) {
            grid[rand() % 15 + 4][rand() % 20 + 1] = rand()%2;
        }
    }
#endif
    vector<vector<int>> grid{
            {0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,0,0,1,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1},
            {0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0},
            {0,0,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,1},
            {0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
            {1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0},
            {0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,1},
            {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0},
            {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
            {0,1,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
            {0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
            {0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
            {0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
            {0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0},
            {0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0}
    };



    clock_t start = clock();
    int res = Solution().uniquePathsWithObstacles_memo(grid);
    clock_t end = clock();
    std::cout << "memo: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000  << "ms" << std::endl;

    start = clock();
    res = Solution().uniquePathsWithObstacles_dp(grid);
    end = clock();
    std::cout << "dp: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000  << "ms" << std::endl;

    start = clock();
    res = Solution().uniquePathsWithObstacles(grid);
    end = clock();
    std::cout << "dfs: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000  << "ms" << std::endl;
    return 0;
}

