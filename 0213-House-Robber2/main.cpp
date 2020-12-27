/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/27
***********************************/

#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

/**
 * 分解成两个线性问题 !!!!
 */

/// 考虑的状态是 [start, end] [index ...size]

/// 时间复杂度 O(n^2)
/// 空间负责度 O(n)
class Solution {
    /// 一个环形问题，分成了两个线性问题
    /// 是这题的巧妙
    int tryStart(vector<int>& nums, int start, int end) {
        if (start > end)
            return 0;

        int maxValue = 0;
        for (int i = start; i <= end; ++i) {
            maxValue = std::max(maxValue, nums[i] + tryStart(nums, i + 2, end));
        }
        return maxValue;
    }

    int tryStart_memo(vector<int> &nums, int start, int end, vector<int> &memo) {
        if (start > end)
            return 0;

        if (memo[start] != -1) {
            return memo[start];
        }

        int maxValue = 0;
        for (int i = start; i <= end; ++i) {
            maxValue = std::max(maxValue, nums[i] + tryStart_memo(nums, i + 2, end, memo));
        }
        memo[start] = maxValue;
        return maxValue;
    }

    int tryStart_dp(vector<int> &nums, int start, int end) {
        vector<int> dp(nums.size(), 0);
        dp[end + 1] = 0;
        for (int i = end; i >= start; --i) {
            int maxValue = 0;
            for (int j = i; j <= end; ++j) {
                maxValue = std::max(maxValue, nums[j] + (j + 2 <= end ? dp[j + 2] : 0));
            }
            dp[i] = maxValue;
        }
        return dp[start];
    }

    int tryStart_dp_v2(vector<int> &nums, int start, int end) {
        //vector<int> dp(nums.size(), 0);
        //dp[start] = nums[start];
        int dp_n_2 = 0;
        int dp_n_1 = nums[start];
        int dp;
        for (int i = start + 1; i <= end; i++) {
            dp = std::max(dp_n_1, nums[i] + dp_n_2);
            dp_n_2 = dp_n_1;
            dp_n_1 = dp;
        }
        return dp;//dp[end];
    }

public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        if (nums.size() == 2)
            return max(nums[0], nums[1]);
        return std::max(tryStart(nums, 0, nums.size() - 2), tryStart(nums, 1, nums.size() - 1));
    }

    int rob_memo(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        if (nums.size() == 2)
            return max(nums[0], nums[1]);
        vector<int> memo1 = vector<int>(nums.size(), -1);
        vector<int> memo2 = vector<int>(nums.size(), -1);
        return std::max(tryStart_memo(nums, 0, nums.size() - 2, memo1), tryStart_memo(nums, 1, nums.size() - 1, memo2));
    }

    int rob_dp(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        if (nums.size() == 2)
            return max(nums[0], nums[1]);
        return std::max(tryStart_dp(nums, 0, nums.size() - 2), tryStart_dp(nums, 1, nums.size() - 1));
    }

    int rob_dp_2(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        if (nums.size() == 2)
            return max(nums[0], nums[1]);
        return std::max(tryStart_dp_v2(nums, 0, nums.size() - 2), tryStart_dp_v2(nums, 1, nums.size() - 1));
    }
};

int main() {

    vector<int> nums {
      1,2,1,1
    };
    clock_t start = clock();
    int res = Solution().rob(nums);
    clock_t end = clock();
    std::cout << "recur: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().rob_memo(nums);
    end = clock();
    std::cout << "memo: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().rob_dp(nums);
    end = clock();
    std::cout << "dp: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().rob_dp_2(nums);
    end = clock();
    std::cout << "dp: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;
    return 0;
}

