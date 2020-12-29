/**********************************
 * File:     main.cpp
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/29
 ***********************************/
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    int maxAmount;
    vector<int> memo;
    /// 返回值可以不用通过传参
  int tryCoinChange(vector<int>& coins, int amount) {
      if (amount == 0)
          return 0;

        if (memo[amount] != -1) {
            return memo[amount];
        }

      int res = maxAmount;
      for (auto coin : coins) {
          if (amount >= coin) {
              res = std::min(res, 1 + tryCoinChange(coins, amount - coin));
          }
      }
      return memo[amount] = res;
  }

  /// 经验教训，减少状态数，是否有必要增加一个递归参数
  int tryCoinChange_dp(vector<int>& coins, int amount) {
      if (coins.size() == 0)
          return 0;
      maxAmount = amount + 1;

      vector<int> memo(maxAmount, -1);
      memo[0] = 0;
      for (int i = 1; i <= amount; ++i) {
          int res = maxAmount;
          for (int coin : coins) {
              if (i >= coin) {
                  res = std::min(res, 1 + memo[i - coin]);
              }
          }
          memo[i] = res;
      }
      return memo[amount] == maxAmount ? -1 : memo[amount];
  }

public:
  /// 最少的硬币凑成这个数
  int coinChange(vector<int>& coins, int amount) {
     if (coins.size() == 0)
          return 0;
    maxAmount = amount + 1;
    memo = vector<int>(maxAmount, -1);
    int res = tryCoinChange(coins, amount);
    return res == maxAmount ? -1 : res;
  }

    int coinChange_dp(vector<int>& coins, int amount) {
        return tryCoinChange_dp(coins, amount);
    }
};

int main() {

    vector<int> nums{1, 2, 5};
    std::cout << Solution().coinChange(nums, 11) << std::endl;
    std::cout << Solution().coinChange_dp(nums, 11) << std::endl;

    vector<int> nums2{2};
    std::cout << Solution().coinChange(nums2, 3) << std::endl;
    std::cout << Solution().coinChange_dp(nums2, 3) << std::endl;

    vector<int> nums3{1};
    std::cout << Solution().coinChange(nums3, 2) << std::endl;
    std::cout << Solution().coinChange_dp(nums3, 2) << std::endl;

  return 0;
}
