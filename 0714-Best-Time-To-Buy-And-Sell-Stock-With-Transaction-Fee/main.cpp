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
     *  T[i][k][0] 第i天后，身上没有股票的总收益
     *  T[i][k][1] 第i天后，身上还有股票的总收益
     *
     *  初始情况
     *  T[0][0][0] = 0
     *  T[0][0][1] = -price[0]
     *
     *  T[i][k][0] = max{T[i-1][k][0], T[i-1][k][1] + prices[i] - fee}
     *  /// 买入k计数一次
     *  T[i][k][1] = max{T[i-1][k][1], T[i-1][k-1][0] - prices[i]}
     */
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n <= 1) return 0;

        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }
        return dp[n-1][0];
    }
};

int main() {
    vector<int> prices{1, 3, 2, 8, 4, 9};
    int fee = 2;

    std::cout << Solution().maxProfit(prices, fee) << std::endl;

    return 0;
}
