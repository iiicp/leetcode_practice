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

    int dp1(vector<int> &prices) {
        int n = prices.size();
//        vector<vector<int>> dp(n, vector<int>(2, 0));
//        dp[0][0] = 0;
//        dp[0][1] = -prices[0];

        int profit0 = 0, profit1 = -prices[0];

        for (int i = 1; i < n; ++i) {
//            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            int newProfit0 = max(profit0, profit1 + prices[i]);
//            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            int newProfit1 = max(profit1, profit0 - prices[i]);
            profit0 = newProfit0;
            profit1 = newProfit1;
        }
        return profit0;//dp[n-1][0]
    }

    int dp2(int k, vector<int>& prices) {
        int n = prices.size();
//        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));
        vector<vector<int>> dp(k+1, vector<int>(2, 0));

        /// 初始化最后两层所有的情况
        for (int i = 1; i <= k; ++i) {
            dp[i][0] = 0;
            dp[i][1] = -prices[0];
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[j][0] = max(dp[j][0], dp[j][1] + prices[i]);
                /// 买入计数一次
                dp[j][1] = max(dp[j][1], dp[j-1][0] - prices[i]);
            }
        }
        return dp[k][0];
    }
public:
    /**
     *  T[0][0][0] = 0
     *  T[0][0][1] = -prices[0]
     *  T[i][k][0] = max{T[i-1][k][0], T[i-1][k][1] + prices[i]}
     *  /// 买入k计数一次
     *  T[i][k][1] = max{T[i-1][k][1], T[i-1][k-1][0] - prices[i]}
     */
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n <= 1 || k <= 0) return 0;

        /// 买卖次数到顶了 --> 无限
        if (k >= n/2) {
            /// 与k无关了
            return dp1(prices);
        }else {
            /// 有限次，与k有关, 两者具体迭代数组会有差异
            return dp2(k, prices);
        }
    }
};

int main() {
    vector<int> prices{2,4,1};
    std::cout << Solution().maxProfit(2, prices) << std::endl;

    vector<int> prices2{3,2,6,5,0,3};
    std::cout << Solution().maxProfit(2, prices2) << std::endl;
    return 0;
}