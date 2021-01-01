/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2021/1/1
***********************************/

#include <string>
#include <vector>
#include <iostream>

/// 最长公共子串
using namespace std;

class Solution {
    /// 考虑以m-1结尾的和以n-1结尾的串，如果s[m-1]和s[n-1]不相等，即以m-1和n-1结尾的公共子串为0, 这一条路已经结束
    /// 否则s[m][n] = 1 + s[m][n]
    /// s1[0, m), s2[0, n)
    int LCS_recur(string &s1, int m, string &s2, int n) {
        if (m == 0 || n == 0)
            return 0;
        if (s1[m-1] == s2[n-1]) {
            /// std::cout << s1[m-1] << ", " << s2[n-1] << std::endl;
            return 1 + LCS_recur(s1, m - 1, s2, n - 1);
        }
        return 0;
    }

    vector<vector<int>> memo;
    int LCS_memo(string &s1, int m, string &s2, int n) {
        if (m == 0 || n == 0)
            return 0;

        if (memo[m][n] != -1)
            return memo[m][n];

        if (s1[m-1] == s2[n-1]) {
            /// std::cout << s1[m-1] << ", " << s2[n-1] << std::endl;
            return memo[m][n] = 1 + LCS_memo(s1, m - 1, s2, n - 1);
        }
        return 0;
    }

    /// 考虑空串，边界更加清晰
    int LCS_dp(string &s1, string &s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i = 0; i <= n; ++i)
            dp[0][i] = 0;
        for (int i = 0; i <= m; ++i)
            dp[i][0] = 0;

        int maxValue = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxValue = max(maxValue, dp[i][j]);
                }
                else
                    dp[i][j] = 0;
            }
        }
        return maxValue;
    }

public:
    int lengthOfLCS(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        int maxValue = 0;
        for (int i = m; i >= 0; i--)
            for (int j = n; j >= 0; j--) {
                maxValue = max(maxValue, LCS_recur(s1, i, s2, j));
            }
        return maxValue;
    }

    int lengthOfLCS_memo(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        memo = vector<vector<int>>(m+1, vector<int>(n+1, -1));
        int maxValue = 0;
        for (int i = m; i >= 0; i--)
            for (int j = n; j >= 0; j--) {
                maxValue = max(maxValue, LCS_memo(s1, i, s2, j));
            }
        return maxValue;
    }

    int lengthOfLCS_dp(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        if (m == 0 || n == 0)
            return 0;
        return LCS_dp(s1, s2);
    }
};

int main() {

    string s1 = "caipeng";
    string s2 = "hello,caipengpeng";
    std::cout << Solution().lengthOfLCS(s1, s2) << std::endl;
    std::cout << Solution().lengthOfLCS_memo(s1, s2) << std::endl;
    std::cout << Solution().lengthOfLCS_dp(s1, s2) << std::endl;

    return 0;
}