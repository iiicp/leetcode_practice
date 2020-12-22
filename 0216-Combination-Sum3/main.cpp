/***********************************
* File:     main.cpp.c
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/22
***********************************/

#include <vector>
#include <iostream>

using namespace std;

class Solution {

    void dfs(int k, int n, int start, vector<int> &cur_res, vector<vector<int>> &res) {
        if (cur_res.size() > k) {
            return;
        }
        if (cur_res.size() == k && n == 0) {
            res.push_back(cur_res);
            return;
        }

        /// 候选集中没有重复的元素
        /// 每次候选集逐渐缩小，不会出现重复选取，也不会出现重复的组合

        /// 如果候选集中有重复的元素，重复的元素避免重复选取，首先要进行排序，然后利用3sum的规则
        /// 当前元素和前面元素比较，如果相等，当前元素就不用选择了（对于组合）
        for (int i = start; i <= 9; ++i) {
            if (n >= i) {
                cur_res.push_back(i);
                dfs(k, n - i, i + 1,cur_res, res);
                cur_res.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {

        vector<vector<int>> res;
        if (k <= 0)
            return res;

        vector<int> cur_path;
        dfs(k, n, 1, cur_path, res);

        return res;
    }
};

int main() {

    vector<vector<int>> res = Solution().combinationSum3(3, 9);
    for (auto &v : res) {
        std::cout << "[";
        for (auto &n : v) {
            std:cout << n << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}