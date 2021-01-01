/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/31
***********************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int tryCombinationSum4(vector<int>& nums, int index, int target, vector<int> &path) {
        if (target == 0) {
            for (auto n : path)
                std::cout << n << " ";
            std::cout << std::endl;
            return 1;
        }

#if 0
        /// 无重复的
        int res = 0;
        if (index > 0) {
            res = tryCombinationSum4(nums, index - 1, target, path);
        }

        if (target >= nums[index]) {
            path.push_back(nums[index]);
            res += tryCombinationSum4(nums, index, target - nums[index], path);
            path.pop_back();
        }
#else
        /// 可能有重复，但是顺序相关的
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (target >= nums[i]) {
                path.push_back(nums[i]);
                res += tryCombinationSum4(nums, index, target - nums[i], path);
                path.pop_back();
            }
        }
#endif

        return res;
    }

    vector<int> memo;
    int combinationSum4_backtrace(vector<int>& nums, int target) {
        if (target == 0) {
            return 1;
        }

        if (memo[target] != INT_MAX)
            return memo[target];

        /// 没有index的情况下，for循环搞起
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (target >= nums[i]) {
                res += combinationSum4_backtrace(nums, target - nums[i]);
            }
        }
        memo[target] = res;
        return res;
    }

    int combinationSum4_dp(vector<int>& nums, int target) {
        return 0;
    }
public:
    int combinationSum4(vector<int>& nums, int target) {

        if (nums.size() == 0 || target <= 0)
            return 0;

        vector<int> path;
        return tryCombinationSum4(nums, nums.size() - 1, target, path);
    }
    int combinationSum4_memo(vector<int>& nums, int target) {

        if (nums.size() == 0 || target <= 0)
            return 0;

        memo = vector<int>(target + 1, INT_MAX);
        return combinationSum4_backtrace(nums, target);
    }
};

int main() {

    vector<int> nums{1,2,3};
    std::cout << Solution().combinationSum4(nums, 4) << std::endl;
    std::cout << Solution().combinationSum4_memo(nums, 4) << std::endl;

    return 0;
}

