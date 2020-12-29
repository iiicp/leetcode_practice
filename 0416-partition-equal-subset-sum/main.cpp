/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/28
***********************************/

#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

/**
 *  注意尽量减小递归函数的参数，也是方便做备忘录
 *
 *  注意此题的备忘录不能用bool变量，因为bool只有两种状态，而这两种状态都是合法的
 *  备忘录的初始必须要是非法状态，即第三种状态
 */
class Solution {

    /// 从最后一个向前考虑看看
    /// 0-1背包问题
    bool tryPartition(vector<int>& nums, int index, int sum) {
      if (index == 0)
        return sum == nums[0] || sum == 0;
      if (sum < 0)
        return false;

      bool res1 = tryPartition(nums, index - 1, sum);
      bool res2 = false;
      if (sum > nums[index]) {
          res2 = tryPartition(nums, index - 1, sum - nums[index]);
      }
      return res1 || res2;
    }

    vector<vector<int>> memo;
    bool tryPartition_memo(vector<int>& nums, int index, int sum) {
      if (index == 0)
        return sum == nums[0] || sum == 0;
      if (sum < 0)
        return false;

      if (memo[index][sum] != -1)
        return memo[index][sum] == 1;

      bool res1 = tryPartition_memo(nums, index - 1, sum);
      bool res2 = false;
      if (sum >= nums[index]) {
        res2 = tryPartition_memo(nums, index - 1, sum - nums[index]);
      }
      memo[index][sum] = res1 || res2;
      return res1 || res2;
    }

    bool tryPartition_dp(vector<int>& nums) {
      int n = nums.size();
      if (n == 0) return false;
      int sum = 0;
      for (int i = 0; i < n; ++i)
        sum += nums[i];

      if (sum % 2 != 0) return false;
      int halfSum = sum/2;
      vector<vector<bool>> dp(n, vector<bool>(halfSum+1, false));

      /// 第一行作为初始化条件
      for (int i = 0; i <= halfSum; ++i) {
        dp[0][i] = (i == 0 || i == nums[0]) ? true : false;
      }

      for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= halfSum; ++j) {
          dp[i][j] = dp[i-1][j] || (j >= nums[i] ? dp[i-1][j-nums[i]] : false);
        }
      }
      return dp[n-1][halfSum];
    }

  bool tryPartition_dp2(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return false;
    int sum = 0;
    for (int i = 0; i < n; ++i)
      sum += nums[i];

    if (sum % 2 != 0) return false;
    int halfSum = sum/2;
    vector<vector<bool>> dp(2, vector<bool>(halfSum+1, false));

    /// 第一行作为初始化条件
    for (int i = 0; i <= halfSum; ++i) {
      dp[0][i] = (i == 0 || i == nums[0]) ? true : false;
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j <= halfSum; ++j) {
        dp[i % 2][j] = dp[(i-1) % 2][j] || (j >= nums[i] ? dp[(i-1)%2][j-nums[i]] : false);
      }
    }
    return dp[(n-1)%2][halfSum];
  }

public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return false;
        int sum = 0;
        for (int i = 0; i < n; ++i)
            sum += nums[i];

        if (sum % 2 != 0) return false;

        memo = vector<vector<int>>(n, vector<int>(sum/2+1, -1));

        return tryPartition_memo(nums, n - 1, sum/2);
    }

    bool canPartition_dp(vector<int>& nums) {
      return tryPartition_dp(nums);
    }

    bool canPartition_dp2(vector<int>& nums) {
      return tryPartition_dp2(nums);
    }
};


int main() {

    srand(time(NULL));

    vector<int> nums(200, 0);
    int halfSum = 0;
    for (int i = 0; i < 100; ++i) {
      nums[i] = rand() % 100;
      halfSum += nums[i];
    }

    for (int i = 100; i < 200; ++i) {
      nums[i] = nums[199 - i];
    }

    clock_t start = clock();
    bool res = Solution().canPartition(nums);
    clock_t end = clock();
    std::cout << res << std::endl;
    std::cout << "time: " << (double)(end-start)/1000 << "ms" << std::endl;
    start = clock();
    res = Solution().canPartition_dp(nums);
    end = clock();
    std::cout << res << std::endl;
    std::cout << "time: " << (double)(end-start)/1000 << "ms" << std::endl;
    start = clock();
    res = Solution().canPartition_dp2(nums);
    end = clock();
    std::cout << res << std::endl;
    std::cout << "time: " << (double)(end-start)/1000 << "ms" << std::endl;

//    vector<int> nums2{1,2,5};
//    std::cout << Solution().canPartition(nums2) << std::endl;
//    std::cout << Solution().canPartition_dp(nums2) << std::endl;
//    std::cout << Solution().canPartition_dp2(nums2) << std::endl;
    return 0;
}

