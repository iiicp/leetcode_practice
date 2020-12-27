/***********************************
* File:     main.cpp.c
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

class Solution {
    /// 考虑偷取[start ... nums.size) 区间
    /// O(n^2)
    int tryStart(vector<int>& nums, int start) {
        if (start >= nums.size())
            return 0;
        int maxValue = 0;
        for (int i = start; i < nums.size(); ++i) {
            maxValue = std::max(nums[i] + tryStart(nums, i + 2), maxValue);
        }
        return maxValue;
    }

    /// 考虑偷取[start ... nums.size) 区间
    /// O(n^2)
    vector<int> memo;
    int tryStart_memo(vector<int>& nums, int start) {
        if (start >= nums.size())
            return 0;
        if (memo[start] != -1) {
            return memo[start];
        }
        int maxValue = 0;
        for (int i = start; i < nums.size(); ++i) {
            maxValue = std::max(nums[i] + tryStart_memo(nums, i + 2), maxValue);
        }
        memo[start] = maxValue;
        return maxValue;
    }

    /// 考虑偷取[start ... nums.size) 区间
    /// O(n^2)
    int tryStart_dp(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 0;
        for (int i = n - 1; i >= 0 ; --i) {
            int maxValue = 0;
            for (int j = i; j < n; ++j) {
                maxValue = std::max(maxValue, nums[j] + ((j + 2 < n) ? dp[j+2] : 0));
            }
            dp[i] = maxValue;
        }
        return dp[0];
    }

    /// 考虑偷取[0, index] 区间
    int tryStart_4(vector<int>& nums, int index) {
        if (index < 0) {
            return 0;
        }

        if (index == 0) {
            return nums[index];
        }

        int maxValue = 0;
        for (int i = index; i >= 0; i--) {
            maxValue = std::max(maxValue, nums[i] + tryStart_4(nums, i - 2));
        }

        return maxValue;
    }

    /// 带记忆化偷取
    /// 考虑偷取[0, index]区间
    vector<int> memo_v4;
    int tryStart_4_memo(vector<int>& nums, int index) {
        if (index < 0)
            return 0;
        if (index == 0)
            return nums[index];

        if (memo_v4[index] != -1) {
            return memo_v4[index];
        }

        int maxValue = 0;
        for (int i = index; i >= 0 ; --i) {
            maxValue = std::max(maxValue, nums[i] + tryStart_4_memo(nums, i - 2));
        }
        memo_v4[index] = maxValue;
        return maxValue;
    }

    /// dp[n+1]=max(dp[n],dp[n−1]+num)
    int tryStart_4_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = std::max(dp[i-1], nums[i] + (i-2 >=0 ? dp[i-2] : 0));
        }
        return dp[n-1];
    }
public:
    int rob(vector<int>& nums) {
        return tryStart(nums, 0);
    }
    int rob_memo(vector<int>& nums) {
        memo = vector<int>(nums.size(), -1);
        return tryStart_memo(nums, 0);
    }

    int rob_dp(vector<int>& nums) {
        return tryStart_dp(nums);
    }

    int rob_v4(vector<int>& nums) {
        return tryStart_4(nums, nums.size() - 1);
    }

    int rob_v4_memo(vector<int>& nums) {
        memo_v4 = vector<int>(nums.size(), -1);
        return tryStart_4_memo(nums, nums.size() - 1);
    }

    int rob_v4_dp(vector<int>& nums) {
        return tryStart_4_dp(nums);
    }
};

int main() {
    vector<int> nums{2,7,9,3,1};
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
    res = Solution().rob_v4(nums);
    end = clock();
    std::cout << "v4: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().rob_v4_memo(nums);
    end = clock();
    std::cout << "v4 memo: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

    start = clock();
    res = Solution().rob_v4_dp(nums);
    end = clock();
    std::cout << "v4 dp: " << res << std::endl;
    std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;
    return 0;
}

