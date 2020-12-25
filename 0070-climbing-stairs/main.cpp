/**********************************
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

/**
 * 考虑n阶台阶的问题，可以尝试考虑n-1阶台阶和n-2阶台阶的子问题，当考虑n-1阶台阶问题继而可以
 * 考虑n-2阶台阶和n-3阶台阶，这就出现了重复子问题，同时当我们考虑1阶台阶和2阶台阶的时候
 * 我们可以求出3阶台阶，继而可以求出4阶、5阶，因此当我们得出子问题的解之后，我们可以得到原问题的解
 *
 * 所以此题满足两个性质：重复子问题和最优子结构 => 可以用动态规划求解，动态规划通常是用来最优值的一种思想
 * 而回溯法通常是求所有解，当然回溯法也可以只求部分解(提前结束，不回溯了）
 *
 * 动态规划可以认为是最优版本，中间的思考过程，应该 递归->记忆化->动归
 */
using namespace std;
class Solution {
  vector<int> memo;

  /// 递归版本
  int tryNStairs1(int n) {
    ++cnt1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    return tryNStairs1(n-2) + tryNStairs1(n-1);
  }

  /// 记忆化版本
  int tryNStairs2(int n) {
    ++cnt2;
    if (n == 1) return 1;
    if (n == 2) return 2;

    int a, b;
    if (memo[n-2] != -1) {
      a = memo[n - 2];
    }else {
      a = tryNStairs2(n-2);
      memo[n-2] = a;
    }
    if (memo[n-1] != -1) {
      b = memo[n - 1];
    } else {
      b = tryNStairs2(n-1);
      memo[n-1] = b;
    }

    return a + b;
  }

  /// 动归版本
  int tryNStairs3(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    int a = 1, b = 2;
    for (int i = 3; i < n; ++i) {
      int t = a + b;
      a = b;
      b = t;
    }
    return a + b;
  }

public:
  int cnt1;
  int cnt2;
  int climbStairs(int n) {
    cnt1 = 0;
    return tryNStairs1(n);
  }

  int climbStairs2(int n) {
    if (n > 1)
      memo = vector<int>(n, -1);
    cnt2 = 0;
    return tryNStairs2(n);
  }

  int climbStairs3(int n) {
    return tryNStairs3(n);
  }
};

int main() {
  int stairs = 34;
  time_t start = clock();
  Solution t1;
  int n  = t1.climbStairs(stairs);
  time_t end = clock();
  std::cout << "stairs: " << stairs << ", climbs " << n << ", call " << t1.cnt1 << std::endl;
  std::cout << "time: " << (double)(end-start)/1000 << "ms" << std::endl;

  start = clock();
  Solution t2;
  n  = t2.climbStairs2(stairs);
  end = clock();
  std::cout << "stairs: " << stairs << ", climbs " << n << ", call " << t2.cnt2 << std::endl;
  std::cout << "time: " << (double)(end-start)/1000 << "ms" << std::endl;

  start = clock();
  Solution t3;
  n  = t3.climbStairs3(stairs);
  end = clock();
  std::cout << "stairs: " << stairs << ", climbs " << n << std::endl;
  std::cout << "time: " << (double)(end-start)/1000 << "ms" << std::endl;
  return 0;
}