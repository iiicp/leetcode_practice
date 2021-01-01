/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/28
***********************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /// 动态规划题型
    /**
     *  状态方程:
     *  t[index][k][0] 表示进行了第index索引后，赚取的收益
     *
     *  初始情况
     *      t[0][0][0] = 0
     *      t[0][0][1] = -prices[0]
     *
     *      t[i][k][0] = max{t[i-1][k][0], t[i-1][k][1] + prices[i]}
     *      /// 买入计数一次
     *      t[i][k][1] = max{t[i-1][k][1], t[i-2][k-1][0] - prices[i]}
     *
     *  此题 k 是无限次数的
     */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
//        vector<vector<int>> dp(n, vector<int>(2, 0));
//        dp[0][0] = 0;
//        dp[0][1] = -prices[0];

        int profit0 = 0, profit1 = -prices[0], profit_1 = 0;

        for (int i = 1; i < n; ++i) {
//            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            int newProfit0 = max(profit0, profit1 + prices[i]);
//            dp[i][1] = max(dp[i-1][1], (i-2>=0 ? dp[i-2][0] : 0)- prices[i]);
            int newProfit1 = max(profit1, profit_1 - prices[i]);
            profit_1 = profit0;
            profit0 = newProfit0;
            profit1 = newProfit1;
        }
        return profit0;//dp[n-1][0];
    }
};

int main() {

    vector<int> prices{1,2,3,0,2};
    std::cout << Solution().maxProfit(prices) << std::endl;

    return 0;
}
