/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/25
***********************************/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Solution {
    int max3(int x, int y, int z) {
        return std::max(x, std::max(y, z));
    }

    /// 递归版本
    /// 具备重复子问题和最优子结构
    int tryInteger(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }
        int maxValue = INT_MIN;
        for (int i = 1; i <= n-1; i++) {
            maxValue = max3(i * tryInteger(n-i), i * (n - i), maxValue);
        }
        return maxValue;
    }

    /// 记忆化搜索
    vector<int> memo;
    int tryInteger_memo(int n) {
        if (n <= 2) {
            return n;
        }

        int maxValue = INT_MIN;
        for (int i = 1; i <= n-1; i++) {
            int a = 0;
            if (memo[n-i] != -1) {
                a = memo[n-i];
            }else {
                a = tryInteger_memo(n-i);
                memo[n - i] = a;
            }
            maxValue = max3(i * a,i * (n - i), maxValue);
        }
        return maxValue;
    }

    /// 动态规划
    int tryInteger_program(int n) {
        vector<int> dp(n + 1, -1);
        dp[1] = 1;
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            int maxvalue = INT_MIN;
            for (int j = 1; j <= i - 1; ++j) {
                maxvalue = max3(maxvalue, j * dp[i - j], j * (i - j));
            }
            dp[i] = maxvalue;
        }

//        for (int i = 1; i < n+1; i++) {
//            std::cout << dp[i] << " ";
//        }
//        std::cout << std::endl;

        return dp[n];
    }
public:
    int integerBreak(int n) {
        return tryInteger(n);
    }

    int integerBreak_memo(int n) {
        memo = vector<int>(n, -1);
        return tryInteger_memo(n);
    }

    int integerBreak_program(int n) {
        return tryInteger_program(n);
    }
};

int main() {

    clock_t start = clock();
    int res = Solution().integerBreak(10);
    clock_t end = clock();
    std::cout << "sum: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().integerBreak_memo(10);
    end = clock();
    std::cout << "sum: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().integerBreak_program(10);
    end = clock();
    std::cout << "sum: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    return 0;
}
