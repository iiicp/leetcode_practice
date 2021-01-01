/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/31
***********************************/

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
    unordered_map<string, bool> dict;


    bool tryWordBreak(string &s, int index, unordered_map<string, bool> &dict) {
        if (index == s.size()) {
            return true;
        }

        for (int i = index; i < s.size(); ++i) {
            if (dict[s.substr(index, i - index + 1)]) {
                if(tryWordBreak(s, i+1,dict))
                    return true;
            }
        }
        return false;
    }

    bool tryWordBreak2(string &s, int index, unordered_map<string, bool> &dict) {
        if (index < 0) {
            return true;
        }

        for (int i = index; i >= 0; --i) {
            if (dict[s.substr(i, index - i + 1)]) {
                if(tryWordBreak2(s, i-1,dict))
                    return true;
            }
        }
        return false;
    }

    /// 空串要考虑
    /// d[i]表示前i个字符，d[i] = d[j] && dict[s.substr(j, i-j)
    bool tryWordBreak2_dp(string &s, unordered_map<string, bool> &dict) {
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[0] = true; /// 表示空串

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && dict[s.substr(j, i - j)]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }

    vector<int> memo;
    bool tryWordBreak_memo(string &s, int index, unordered_map<string, bool> &dict) {
        if (index == s.size()) {
            return true;
        }


        if (index < s.size() && memo[index] != -1)
            return memo[index] == 1;

        for (int i = index; i < s.size(); ++i) {
            if (dict[s.substr(index, i - index + 1)]) {
                if(tryWordBreak_memo(s, i+1,dict)) {
                    if (i+1 < s.size())
                        memo[i+1] = 1;
                    return true;
                }
            }
        }
        if (index < s.size())
            memo[index] = 0;
        return false;
    }



public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for (auto &str : wordDict)
            dict[str] = true;

        return tryWordBreak2(s, s.size() - 1, dict);
    }

    bool wordBreak_memo(string s, vector<string>& wordDict) {
        for (auto &str : wordDict)
            dict[str] = true;
        memo = vector<int>(s.size() + 1, -1);
        return tryWordBreak_memo(s, 0, dict);
    }

    bool wordBreak_dp(string s, vector<string> &wordDict) {
        for (auto &str : wordDict)
            dict[str] = true;
        return tryWordBreak2_dp(s, dict);
    }
};

int main() {

    vector<string> wordDict = {"leet", "code"};
    string s = "leetcode";
//    std::cout << Solution().wordBreak(s, wordDict) << std::endl;
//    std::cout << Solution().wordBreak_memo(s, wordDict) << std::endl;
    std::cout << Solution().wordBreak_dp(s, wordDict) << std::endl;

    vector<string> wordDict2 = {"apple", "pen"};
    string s2 = "applepenapple";
//    std::cout << Solution().wordBreak(s2, wordDict2) << std::endl;
//    std::cout << Solution().wordBreak_memo(s2, wordDict2) << std::endl;
    std::cout << Solution().wordBreak_dp(s2, wordDict2) << std::endl;

    vector<string> wordDict3 = {"cats", "dog", "sand", "and", "cat"};
    string s3 = "catsandog";
//    std::cout << Solution().wordBreak(s3, wordDict3) << std::endl;
//    std::cout << Solution().wordBreak_memo(s3, wordDict3) << std::endl;
    std::cout << Solution().wordBreak_dp(s3, wordDict3) << std::endl;

    return 0;
}