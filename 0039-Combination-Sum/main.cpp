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

    void dfs(vector<int>& candidates, int target, int sum, int start, vector<int> &path, vector<vector<int>> &res) {
        if (sum > target)
            return;
        if (start >= candidates.size())
            return;
        if (sum == target) {
            res.push_back(path);
            return;
        }
        path.push_back(candidates[start]);
        dfs(candidates, target, sum + candidates[start], start, path, res);
        path.pop_back();
        dfs(candidates, target, sum, start + 1, path, res);
    }

    void dfs2(vector<int>& candidates, int target, int index, vector<int> &path, vector<vector<int>> &res) {

        if (target == 0) {
            res.push_back(path);
            return;
        }

        // 每次的候选集
        for (int i = index; i < candidates.size(); ++i) {
            if (target >= candidates[i]) {
                path.push_back(candidates[i]);
                dfs2(candidates, target - candidates[i], i, path, res);
                path.pop_back();
            }
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if (candidates.size() == 0)
            return res;
        vector<int> path;
#if 0
        dfs(candidates, target, 0, 0, path, res);
#else
        dfs2(candidates, target, 0, path, res);
#endif
        return res;
    }
};

int main() {

    vector<int> v{2,3,5};
    int target = 8;
    vector<vector<int>> res = Solution().combinationSum(v, target);
    for (auto &v : res) {
        std::cout << "[";
        for (auto &n : v) {
            std:cout << n << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}