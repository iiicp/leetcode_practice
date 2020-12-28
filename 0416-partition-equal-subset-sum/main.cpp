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

using namespace std;

/**
 *  注意尽量减小递归函数的参数，也是方便做备忘录
 *
 *  注意此题的备忘录不能用bool变量，因为bool只有两种状态，而这两种状态都是合法的
 *  备忘录的初始必须要是非法状态，即第三种状态
 */
class Solution {
    bool tryIndex(vector<int>& nums, int index, int left, int right) {
        if (index == nums.size() && left == right)
            return true;
        if (index == nums.size())
            return false;

        bool res1 = tryIndex(nums, index + 1, left + nums[index], right);
        bool res2 = tryIndex(nums, index + 1, left, right + nums[index]);

        return res1 || res2;
    }

    vector<vector<int>> memo;
    bool tryStart(vector<int>& nums, int index, int sum) {
        if (index == nums.size() && sum == 0)
            return true;
        if (sum < 0 || index == nums.size())
            return false;

        if (memo[index][sum] != -1) {
            return memo[index][sum] == 1;
        }

        memo[index][sum] = tryStart(nums, index + 1, sum - nums[index])
            || tryStart(nums, index + 1, sum);
        return memo[index][sum] == 1;
    }

public:
    bool canPartition(vector<int>& nums) {
        if (nums.size() == 0)
            return false;
        return tryIndex(nums, 0, 0, 0);
    }

    bool canPartition2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0)
            return false;
        int sum = 0;
        for (int i = 0; i < n; ++i)
            sum += nums[i];

        if (sum % 2 != 0)
            return false;

        memo = vector<vector<int>>(n, vector<int>(sum/2 + 1, -1));
        return tryStart(nums, 0, sum/2);
    }
};


int main() {

//    vector<int> nums{1,5,11,5};
//    std::cout << Solution().canPartition(nums) << std::endl;
//    std::cout << Solution().canPartition2(nums) << std::endl;

    vector<int> nums2{1,2,5};
    std::cout << Solution().canPartition(nums2) << std::endl;
    std::cout << Solution().canPartition2(nums2) << std::endl;
    return 0;
}

