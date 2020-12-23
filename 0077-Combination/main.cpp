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

    void dfs(int n, int k, int start, vector<int> &path, vector<vector<int>> &res) {
        if (k == path.size()) {
            res.push_back(path);
            return;
        }

        // 候选集
        for (int i = start; i <= n; ++i) {
              path.push_back(i);
              dfs(n, k, i + 1, path, res);
              path.pop_back();
        }
    }

    // 减枝
    void dfs2(int n, int k, int start, vector<int> &path, vector<vector<int>> &res) {
        if (k == path.size()) {
            res.push_back(path);
            return;
        }

        // 候选集
        // k - path.size()
        // [i, n] -> [i + k - path.size() <= n]
        for (int i = start; i <= n - k + 1 + path.size(); ++i) {
                path.push_back(i);
                dfs2(n, k, i + 1, path, res);
                path.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {

        vector<vector<int>> res;
        if (n == 0) {
            return res;
        }

        vector<int> path;
        dfs2(n, k, 1, path, res);
        return res;
    }
};

int main() {

    vector<vector<int>> res = Solution().combine(4,2);
    for (auto &v : res) {
        std::cout << "[";
        for (auto &n : v) {
            std:cout << n << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}