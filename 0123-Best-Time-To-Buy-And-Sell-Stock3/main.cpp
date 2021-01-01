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
public:
    /**
     *  T[i][k][0] 表示第i天交易之后，身上没有股票所带来的的最大收益
     *  T[i][k][1] 表示第i天交易之后，身上还有留有一张股票所带来的最大收益
     *
     *  T[0][0][0] = 0;
     *  T[0][0][1] = -prices[0]
     *
     *  T[0][1][0] = 0;
     *  T[0][1][1] = -prices[0]
     *
     *  T[i][k][0] = max{T[i-1][k][0], T[i-1][k][1] + prices[i]}
     *  T[i][k][1] = max{T[i-1][k][1], T[i-1][k-1][0] - prices[i]}
     *
     *  T[i][2][0] = max{T[i-1][2][0], T[i-1][2][1] + prices[i]}
     *  T[i][2][1] = max{T[i-1][2][1], T[i-1][1][1] - prices[i]}
     *  T[i][1][0] = max{T[i-1][1][0], T[i-1][1][1] + prices[i}}
     *  /// 买入计数一次
     *  T[i][1][1] = max{T[i-1][1][1], T[i-1][0][0] - prices[i]}
     */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
//        vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(2, 0)));
//
//        /// 要将第二三维的基础状态列出来
//        dp[0][1][0] = 0;
//        dp[0][1][1] = -prices[0];
//        dp[0][2][0] = 0;
//        dp[0][2][1] = -prices[0];

        int dpOneZero = 0, dpOneOne = -prices[0], dpTwoZero = 0, dpTwoOne = -prices[0];

        for (int i = 1; i < n; ++i) {
//            dp[i][2][0] = max(dp[i-1][2][0], dp[i-1][2][1] + prices[i]);
            dpTwoZero = max(dpTwoZero, dpTwoOne + prices[i]);
//            dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - prices[i]);
            dpTwoOne = max(dpTwoOne, dpOneZero - prices[i]);
//            dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i]);
            dpOneZero = max(dpOneZero, dpOneOne + prices[i]);
//            dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]);
            dpOneOne = max(dpOneOne, -prices[i]);
        }
        return dpTwoZero;//dp[n-1][2][0];
    }
};

int main() {
    vector<int> prices{3,3,5,0,0,3,1,4};
    std::cout << Solution().maxProfit(prices) << std::endl;

    vector<int> prices1{1,2,3,4,5};
    std::cout << Solution().maxProfit(prices1) << std::endl;
    return 0;
}

