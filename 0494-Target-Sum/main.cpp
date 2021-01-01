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
    vector<vector<int>> memo;

    /// 注意S的范围是有正有负的，想办是法让他在正的范围去做
    /// 最小的负数是-1000，最大的正数是1000, 所以范围是[0~2000]
    int tryFindTargetSumWays(vector<int>& nums, int index, int S) {
        if (index < 0 && S == 0) {
            return 1;
        }
        if (index < 0) {
            return 0;
        }

        /// 要对溢出做保护
        if (S >= 1001 || S < -1000)
            return 0;

        /// 要对数组范围做保护
        if (memo[index][S + 1000] != -1)
            return memo[index][S + 1000];

        return memo[index][S + 1000] = tryFindTargetSumWays(nums, index - 1, S-nums[index])
        + tryFindTargetSumWays(nums, index - 1, S+nums[index]);
    }
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        /// 数据范围和最多是2000
        memo = vector<vector<int>>(nums.size(), vector<int>(2001, -1));
        return tryFindTargetSumWays(nums, nums.size() - 1, S);
    }
};

int main() {

    vector<int> nums{1,1,1,1,1};
    int S = 3;
    std::cout << Solution().findTargetSumWays(nums, S) << std::endl;

    return 0;
}