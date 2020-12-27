/**********************************
 * File:     main.cpp
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/26
 ***********************************/
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
/**
 *  输入：s = "226"
    输出：3
    解释：它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
 */
using namespace std;

/**
 *  错误认知
 *  对计数规则的，怎样才算一次，一定要思考清楚
 *  1，对num认知不清，从头扫到尾才算一次（从起点到终点算一次）
 *  2，对于递归重复计数的问题，要用最基本的子问题去计数。（所以递归的出口情况要判断清楚）
 */

class Solution {

  /// [start, ...)
  int tryStringIndex(string &s, int start) {

    /// 到达终点才算一次
    if (start >= s.size()) {
      return 1;
    }

    if (s[start] == '0')
        return 0;

    /// 递归树，每次有两种选择
    int res = tryStringIndex(s, start + 1);
    if (start + 1 < s.size() && s.substr(start, 2) <= "26") {
        res += tryStringIndex(s, start + 2);
    }
    return res;
  }

  vector<int> memo;
  int tryStringIndex_memo(string &s, int start) {

        /// 到达终点才算一次
     if (start >= s.size()) {
            return 1;
     }

     if (s[start] == '0')
         return 0;

        /// 对于备忘录退出条件要干净利落
     if (memo[start] != -1) {
         return memo[start];
     }

        /// 递归树，每次有两种选择
     int res = tryStringIndex_memo(s, start + 1);
     if (start + 1 < s.size() && s.substr(start, 2) <= "26") {
        res += tryStringIndex_memo(s, start + 2);
     }
     memo[start] = res;
     return res;
  }

  /// 动态规划，迭代思维
  int tryStringIndex_dp(string &s) {
      /// 关于迭代的初值设定，也就是递归版本的出口
      int n = s.size();
      vector<int> dp(n + 1, 0);
      dp[n] = 1;

      for (int i = n - 1; i >= 0 ; --i) {
          if (s[i] != '0') {
              dp[i] = dp[i + 1];
              if (i + 2 <= n && s.substr(i, 2) <= "26")
                  dp[i] += dp[i + 2];
          }
      }
      return dp[0];
  }

public:
  int numDecodings(string s) {
      return tryStringIndex(s, 0);
  }

  int numDecodings_memo(string s) {
    memo = vector<int>(s.size(), -1);
    return tryStringIndex_memo(s, 0);
  }

  int numDecodings_dp(string s) {
    return tryStringIndex_dp(s);
  }
};

int main() {

  std::cout << Solution().numDecodings("226") << std::endl;
  std::cout << Solution().numDecodings("12") << std::endl;
  std::cout << Solution().numDecodings("102") << std::endl;

  std::cout << Solution().numDecodings_memo("226") << std::endl;
  std::cout << Solution().numDecodings_memo("12") << std::endl;
  std::cout << Solution().numDecodings_memo("102") << std::endl;

  std::cout << Solution().numDecodings_dp("226") << std::endl;
  std::cout << Solution().numDecodings_dp("12") << std::endl;
  std::cout << Solution().numDecodings_dp("102") << std::endl;
  return 0;
}
