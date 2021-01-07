/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2021/1/2
***********************************/

#include <vector>
#include <iostream>

using namespace std;
/// error !!!!!!
class Solution {
    int tryWiggleMaxLength(vector<int> &nums, int n, bool greater) {
        if (n < 0)
            return 0;
        int res = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (greater) {
                if (nums[n] > nums[i]) {
                    res += 1 + tryWiggleMaxLength(nums, i, false);
                }
            }else {
                if (nums[n] < nums[i]) {
                    res += 1 + tryWiggleMaxLength(nums, i, true);
                    std::cout << res << std::endl;

                }
            }
        }
        return res;
    }

public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 1)
            return 1;
        if (nums.size() == 2)
            return 0;

        int n = nums.size();
        int maxValue = 0;
        for (int i = n - 1; i >= 0; i--) {
            maxValue = max(maxValue, tryWiggleMaxLength(nums, i, true));
        }

        int maxValue2 = 0;
        for (int i = n - 1; i >= 0; i--) {
            maxValue2 = max(maxValue2, tryWiggleMaxLength(nums, i, false));
        }

        return max(maxValue, maxValue2);
    }
};

int main() {

    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    std::cout << Solution().wiggleMaxLength(nums) << std::endl;

    return 0;
}