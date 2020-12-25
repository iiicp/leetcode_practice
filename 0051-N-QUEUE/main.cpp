/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/24
***********************************/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
    int col;
    vector<string> generator(vector<int> &path) {
        vector<string> res;
        for (int i = 0; i < path.size(); ++i) {
            string str;
            int target = path[i];
            for (int j = 0; j < col; ++j) {
                if (target == j) {
                    str += 'Q';
                }else {
                    str += '.';
                }
            }
            res.push_back(str);
        }
        return res;
    }

    vector<bool> colUsed;
    vector<bool> diag1;
    vector<bool> diag2;

    void dfs(int row,  vector<int> &cur, vector<vector<string>> &res) {
        if (row == col) {
            res.push_back(generator(cur));
            return;
        }

        for (int i = 0; i < col; ++i) {
            if (!colUsed[i] && !diag1[row + i] && !diag2[i - row + col - 1]) {
                colUsed[i] = true;
                diag1[row + i] = true;
                diag2[i - row + col - 1] = true;
                cur.push_back(i);
                dfs(row + 1, cur, res);
                cur.pop_back();
                colUsed[i] = false;
                diag1[row + i] = false;
                diag2[i - row + col - 1] = false;
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        if (n == 0)
            return res;
        col = n;
        colUsed = vector<bool>(col, false);
        diag1 = vector<bool>(2 * col - 1, false);
        diag2 = vector<bool>(2 * col - 1, false);
        vector<int> path;
        dfs(0, path, res);
        return res;
    }
};

int main() {

    vector<vector<string>> res = Solution().solveNQueens(8);
    std::cout << res.size() << std::endl;
#if 0
    for (auto &v : res) {
        std::cout << std::endl;
        for (auto &str : v) {
            std::cout << str << std::endl;
        }
    }
#endif

    return 0;
}