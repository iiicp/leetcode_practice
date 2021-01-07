/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2021/1/7
***********************************/

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Solution {

public:
    string longestPalindrome(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        /// 考虑 s[i..j] 若 i == j 则 s[i..j] = s[i]==s[j] && s[i+1..j-1]
        /// 边界条件是 [i+1..j-1]是否能成为区间
        vector<vector<bool>> dp(len, vector<bool>(len, false));
        int begin = 0, maxLen = 1;
        for (int i = 0; i < len; ++i)
            dp[i][i] = true;

        for (int j = 1; j < len; ++j) {
            for (int i = 0; i < j; ++i)  {
                if (s[i] != s[j])
                    dp[i][j] = false;
                else {
                    /// 若 s[i+1,j-1]不构成区间，即判断的是最原始的两个字符，那么就直接设置为true
                    /// (j-1) - (i+1) + 1 < 2 => j - i < 3 此时直接为true
                    if (j - i < 3) {
                        dp[i][j] = true;
                    }else {
                        dp[i][j] = dp[i+1][j-1];
                    }
                }

                if (dp[i][j] == true && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }

        return s.substr(begin, maxLen);
    }
};

int main() {

    string str = "cbbd";
    string res = Solution().longestPalindrome(str);
    std::cout << res << std::endl;

    return 0;
}
