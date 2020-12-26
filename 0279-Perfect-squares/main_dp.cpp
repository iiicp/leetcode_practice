/**********************************
 * File:     main_dp.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/26
 ***********************************/
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <queue>

using namespace std;

/**
 * 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
 *  输入: n = 12
    输出: 3
    解释: 12 = 4 + 4 + 4
 */

/**
 * 此题犯了个错，没有考虑n本身就是个完全平方数的情况 !!!!
 *  即此题最小值可能为1
 */
class Solution {
  /// 递归版本
  int tryN(int n) {
    if (n <= 2)
      return n;
    int minValue = n;
    for (int i = 1; i * i <= n; ++i) {
      if (i * i == n) {
        minValue = 1;
      } else {
        int a = (int)sqrt(n - i * i);
        if (n - i * i == a * a) {
          minValue = 2;
        } else {
          minValue = std::min(1 + tryN(n - i * i), minValue);
        }
      }
    }
    return minValue;
  }

  /// 记忆化版本
  vector<int> memo;
  int tryN_memo(int n) {
    if (n <= 2)
      return n;

    int minValue = n;
    for (int i = 1; i * i <= n; ++i) {
      if (n - i * i == 0) {
        minValue = 1;
      }else {
        int a = (int)sqrt(n - i * i);
        if (n - i * i == a * a) {
          minValue = 2;
        } else {
          int a = 0;
          if (memo[n - i * i] != -1) {
            a = memo[n - i * i];
          } else {
            a = tryN_memo(n - i * i);
            memo[n - i * i] = a;
          }
          minValue = std::min(1 + a, minValue);
        }
      }
    }
    return minValue;
  }

  /// 动态规划
  int tryN_dp(int n) {
    vector<int> dp(n + 1, -1);
    dp[1] = 1; dp[2] = 2;
    for (int i = 3; i <= n; ++i) {
      int minValue = i;
      int j = 1, a;
      while ((a = j * j) <= i) {
        if (a == i) {
          minValue = 1;
        }else {
          minValue = std::min(1 + dp[i - a], minValue);
        }
        ++j;
      }
      dp[i] = minValue;
    }
    return dp[n];
  }

public:
  int numSquares(int n) {
    if (n == 0)
      return 0;
    return tryN(n);
  }

  int numSquares_memo(int n) {
    if (n == 0)
      return 0;
    memo = vector<int>(n+1, -1);
    return tryN_memo(n);
  }

  int numSquares_dp(int n) {
    if (n <= 2)
      return n;
    return tryN_dp(n);
  }

  int numSquares_grap(int n) {

    assert(n > 0);

    queue<pair<int, int>> q;
    q.push(make_pair(n, 0));

    vector<bool> visited(n+1, false);
    visited[n] = true;

    while (!q.empty()) {
      int num = q.front().first;
      int level = q.front().second;
      q.pop();

      if (num == 0)
        return level;

      int i = 1;
      int c;
      while (true) {
        c = num - i * i;
        if (c < 0) break;
        if (c == 0)
          return level+1;
        if (!visited[c]) {
          q.push(make_pair(c, level + 1));
          visited[c] = true;
        }
        i++;
      }
    }

    return 0;
  }
};

int main() {

  int n = 12;

  clock_t start = clock();
  int res = Solution().numSquares_dp(n);
  clock_t end = clock();
  std::cout << "mimum(dp)" << res << std::endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  start = clock();
  res = Solution().numSquares_memo(n);
  end = clock();
  std::cout << "mimum(memo): " << res << std::endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  start = clock();
  res = Solution().numSquares_grap(n);
  end = clock();
  std::cout << "mimum(grap): " << res << std::endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  start = clock();
  res = Solution().numSquares(n);
  end = clock();
  std::cout << "mimum(recur): " << res << std::endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  return 0;
}
