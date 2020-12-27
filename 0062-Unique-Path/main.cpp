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

class Solution {
    /**
     * 此题没有强调是最小路径和最大路径
     *
     * 但是此题具备最优子结构和重复子问题
     * 所以从dfs思路去入口
     */
    int tryStart_dfs(int m, int n, int x, int y) {
        /// 到达终点算一个路径
        if (x == m - 1 && y == n - 1)
            return 1;

        /// 每次有两种选择，向下、向右
        int res = 0;
        if (x + 1 <= m - 1) {
            res += tryStart_dfs(m, n, x + 1, y);
        }
        if (y + 1 <= n - 1) {
            res += tryStart_dfs(m, n, x, y + 1);
        }
        return res;
    }

    vector<vector<int>> memo;
    int tryStart_memo(int m, int n, int x, int y) {
        /// 到达终点算一个路径
        if (x == m - 1 && y == n - 1)
            return 1;

        if (memo[x][y] != -1) {
            return memo[x][y];
        }

        /// 每次有两种选择，向下、向右
        int res = 0;
        if (x + 1 <= m - 1) {
            res += tryStart_memo(m, n, x + 1, y);
        }
        if (y + 1 <= n - 1) {
            res += tryStart_memo(m, n, x, y + 1);
        }
        memo[x][y] = res;
        return res;
    }

    int tryStart_dp(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[m-1][n-1] = 1;

        for (int i = m-1; i >= 0; --i) {
            for (int j = n-1; j >= 0; --j) {
                if (i == m - 1 && j == n -1) {
                    continue;
                }
                int a = i+1 < m ? dp[i+1][j] : 0;
                int b = j+1 < n ? dp[i][j+1] : 0;
                dp[i][j] = a + b;
            }
        }
        return dp[0][0];
    }

public:
    int uniquePaths(int m, int n) {
        return tryStart_dfs(m, n, 0, 0);
    }

    int uniquePaths_memo(int m, int n) {
        memo = vector<vector<int>>(m, vector<int>(n, -1));
        return tryStart_memo(m, n, 0, 0);
    }

    int uniquePaths_dp(int m, int n) {
        return tryStart_dp(m, n);
    }
};

int main() {
    clock_t start = clock();
    int res = Solution().uniquePaths(10,20);
    clock_t end = clock();
    cout << "res: " << res << endl;
    cout << "time: " << (double)(end - start)/1000 << "ms" << endl;

    start = clock();
    res = Solution().uniquePaths_memo(10,20);
    end = clock();
    cout << "res: " << res << endl;
    cout << "time: " << (double)(end - start)/1000 << "ms" << endl;

    start = clock();
    res = Solution().uniquePaths_dp(10,20);
    end = clock();
    cout << "res: " << res << endl;
    cout << "time: " << (double)(end - start)/1000 << "ms" << endl;
    return 0;
}

