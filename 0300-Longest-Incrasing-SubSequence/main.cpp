/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/31
***********************************/

#include <vector>
#include <iostream>

using namespace std;

class Solution {

    /// 每次考查[m,...)
    /// 对于有间断的递归，每次递归只能算一次
    int LIS_recur(vector<int>& nums, int m) {
        /// 长度为1的串，就是它本身
        if (m == 0)
            return 1;

        /// 默认字符就是它本身，就是1
        int temp = 1;
        for (int j = m-1; j >= 0; --j) {
            if (nums[m] > nums[j])
                temp = max(temp, 1 + LIS_recur(nums, j));
        }
        /// std::cout << "("<< nums[m] << ", " << temp << ")" << std::endl;
        return temp;
    }

    vector<int> memo;
    int LIS_memo(vector<int>& nums, int m) {
        if (m == 0)
            return 1;

        if (memo[m] != -1)
            return memo[m];

        int res = 1;
        for (int i = m - 1; i >= 0; --i) {
            if (nums[m] > nums[i])
                res = max(res, 1 + LIS_memo(nums, i));
        }
        return memo[m] = res;
    }

    int LIS_dp(vector<int> &nums) {
        int m = nums.size();
        vector<int> dp(m, 1);

        int maxValue = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = i-1; j >= 0; --j) {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], 1 + dp[j]);
            }
            maxValue = max(maxValue, dp[i]);
        }
        return maxValue;
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        if (m == 0)
            return 0;

        /// 还需要外面的主控程序配合
        int maxValue = 1;
        for (int i = m - 1; i >= 0; --i) {
            maxValue = std::max(maxValue, LIS_recur(nums, i));
        }
        return maxValue;
    }

    int lengthOfLIS_memo(vector<int>& nums) {
        int m = nums.size();
        if (m == 0)
            return 0;

        memo = vector<int>(m, -1);

        /// 还需要外面的主控程序配合
        int maxValue = 1;
        for (int i = m - 1; i >= 0; --i) {
            maxValue = std::max(maxValue, LIS_memo(nums, i));
        }
        return maxValue;
    }

    int lengthOfLIS_dp(vector<int> &nums) {
        int m = nums.size();
        if (m <= 1)
            return m;
        return LIS_dp(nums);
    }
};

int main() {
    vector<int> nums = {10,9,2,5,4,7,1,3};
    std::cout << Solution().lengthOfLIS(nums) << std::endl;
    std::cout << Solution().lengthOfLIS_memo(nums) << std::endl;
    std::cout << Solution().lengthOfLIS_dp(nums) << std::endl;

//    vector<int> nums2 = {0,1,0,3,2,3};
//    std::cout << Solution().lengthOfLIS(nums2) << std::endl;
    return 0;
}