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
 * 长时跟踪和短时跟踪
 */
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        if (n == 0)
            return 0;
        /// 历史跟踪值
        int res = 0;
        int minPrice = prices[0];
        for (int i = 1; i < n; ++i) {
            res = std::max(res, prices[i] - minPrice);
            /// 短时调整量
            minPrice = std::min(minPrice, prices[i]);
        }
        return res;
    }
};

int main() {
    vector<int> nums{7,1,5,3,6,4};
    std::cout << Solution().maxProfit(nums) << std::endl;
    return 0;
}