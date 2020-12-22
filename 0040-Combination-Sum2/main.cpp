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

    vector<bool> visisted;

    void dfs2(vector<int>& candidates, int target, int sum, int start, vector<int> &path, vector<vector<int>> &res) {
        if (sum > target)
            return;
        if (start > candidates.size()) {
            return;
        }
        if (sum == target) {
            res.push_back(path);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            if (!visisted[i]) {
                if (i > start && candidates[i] == candidates[i - 1] && !visisted[i - 1])
                    continue;
                visisted[i] = true;
                path.push_back(candidates[i]);
                dfs2(candidates, target, sum + candidates[i], i + 1, path, res);
                path.pop_back();
                visisted[i] = false;
//                dfs(candidates, target, sum, i + 1, path, res);
            }
        }
    }

    void dfs(vector<int>& candidates, int target, int index, vector<int> &path, vector<vector<int>> &res) {

        if (target == 0) {
            res.push_back(path);
            return;
        }

        // 每次的候选集
        for (int i = index; i < candidates.size(); ++i) {
            if (!visisted[i]) {
                if (target >= candidates[i]) {
                    if (i > index && candidates[i] == candidates[i-1] && !visisted[i-1])
                        continue;
                    visisted[i] = true;
                    path.push_back(candidates[i]);
                    dfs(candidates, target - candidates[i], i + 1, path, res);
                    path.pop_back();
                    visisted[i] = false;
                }
            }
        }
    }

    // 对于这道题，visited是多余的，因为每次都是选择当前的第一个，并且下次递归，排除了当前第一个
    void dfs(const vector<int> &candidates, int index, int target,
               vector<int>& cur_res, vector<vector<int>>& res){

        if(target == 0){
            res.push_back(cur_res);
            return;
        }

        for(int i = index ; i < candidates.size() ; i ++){
            if(i > index && candidates[i] == candidates[i-1])
                continue;
            if(target >= candidates[i]){
                cur_res.push_back(candidates[i]);
                dfs(candidates, i + 1, target - candidates[i], cur_res, res);
                cur_res.pop_back();
            }
        }

        return;
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if (candidates.size() == 0)
            return res;
        visisted.clear();
        visisted = vector<bool>(candidates.size(), false);
        vector<int> path;

        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, path, res);
//        solve(candidates, 0, target, path, res);
        return res;
    }
};

int main() {

    vector<int> v{2,5,2,1,2};
    int target = 5;
    vector<vector<int>> res = Solution().combinationSum2(v, target);
    for (auto &v : res) {
        std::cout << "[";
        for (auto &n : v) {
            std:cout << n << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}