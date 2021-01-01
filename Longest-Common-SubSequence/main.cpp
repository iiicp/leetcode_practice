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

using namespace std;

class Solution {

    /**
     *  每次从两个字符串尾部向前考查 s1[0,m)  s2[0,n)
     *  思考路径，考虑空串的场景，所以左闭右开的方式会好点
     *
     *  比较当前考虑的字符，如果字符相等，递归的考虑之前的串
     *  如果当前字符不等，分两种情况考虑
     */
    int LCS_recur(string &s1, int m, string &s2, int n) {
        /// 空串的场景
        if (m == 0 || n == 0)
            return 0;
        if (s1[m-1] == s2[n-1]) {
            return 1 + LCS_recur(s1, m - 1, s2, n - 1);
        }else {
            return max(LCS_recur(s1, m - 1, s2, n), LCS_recur(s1, m, s2, n-1));
        }
    }

    vector<vector<int>> memo;
    int LCS_recur_memo(string &s1, int m, string &s2, int n) {

        /// 空串的场景
        if (m == 0 || n == 0)
            return 0;

        if (memo[m][n] != -1)
            return memo[m][n];

        int res = 0;
        if (s1[m-1] == s2[n-1]) {
            res = 1 + LCS_recur_memo(s1, m - 1, s2, n - 1);
        }else {
            res = max(LCS_recur_memo(s1, m - 1, s2, n), LCS_recur_memo(s1, m, s2, n-1));
        }
        return memo[m][n] = res;
    }

    vector<vector<int>> dp;
    int LCS_recur_dp(string &s1, string &s2) {
        int m = s1.size(), n = s2.size();
        dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

        /// 初始化
        for (int i = 0; i <= m; ++i) {
            dp[0][i] = 0;
            dp[i][0] = 0;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[m][n];
    }

public:
    /// 搜索字符串s1[0, m-1], s2[0, n-1]的公共子串
    /// 根据dp表从右下角到左上角，来遍历
    void LCS_String(string &s1, string &s2, string lcs, int m, int n) {
        /// 空串了
        if (m == 0 || n == 0) {
            reverse(lcs.begin(), lcs.end());
            std::cout << lcs << std::endl;
            return;
        }

        /// 只有相等的时候，才添加
        if (s1[m-1] == s2[n-1]) {
            LCS_String(s1, s2, lcs + s1[m-1], m - 1, n - 1);
        }else {
            /// 根据dp的抉择逆推
            if (dp[m-1][n] == dp[m][n-1]) {
                /// 相等时，说明有两条路
                LCS_String(s1, s2, lcs, m - 1, n);
                LCS_String(s1, s2, lcs, m, n-1);
            }else if (dp[m-1][n] > dp[m][n-1]) {
                LCS_String(s1, s2, lcs, m - 1, n);
            }else {
                LCS_String(s1, s2, lcs, m, n-1);
            }
        }
    }

public:
    int getMaxLengthCommonSubSequence(string &s1, string &s2) {
        int m = s1.size(), n = s2.size();
        return LCS_recur(s1, m, s2, n);
    }
    int getMaxLengthCommonSubSequence_memo(string &s1, string &s2) {
        int m = s1.size(), n = s2.size();
        memo = vector<vector<int>>(m+1, vector<int>(n+1, -1));
        return LCS_recur_memo(s1, m, s2, n);
    }
    int getMaxLengthCommonSubSequence_dp(string &s1, string &s2) {
        return LCS_recur_dp(s1, s2);
    }
};

int main() {
//    string s1 = "caipeng";
//    string s2 = "cai4caipng4caipg4png";
    string s1 = "ABCBDAB";
    string s2 = "BDCABA";
    int res = Solution().getMaxLengthCommonSubSequence(s1, s2);
    std::cout << res << std::endl;

    res = Solution().getMaxLengthCommonSubSequence_memo(s1, s2);
    std::cout << res << std::endl;

    Solution t;
    res = t.getMaxLengthCommonSubSequence_dp(s1, s2);
    std::cout << res << std::endl;
    t.LCS_String(s1, s2, "", s1.size(), s2.size());

    return 0;
}