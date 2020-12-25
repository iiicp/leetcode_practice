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
    int nNum;
    vector<bool> colUsed;
    vector<bool> diag1;
    vector<bool> diag2;

    void dfs(int row) {
        if (row == col) {
            nNum++;
            return;
        }

        for (int i = 0; i < col; ++i) {
            if (!colUsed[i] && !diag1[row + i] && !diag2[i - row + col - 1]) {
                colUsed[i] = true;
                diag1[row + i] = true;
                diag2[i - row + col - 1] = true;
                dfs(row + 1);
                colUsed[i] = false;
                diag1[row + i] = false;
                diag2[i - row + col - 1] = false;
            }
        }
    }
public:

    int totalNQueens(int n) {
        if (n == 0)
            return 0;
        col = n;
        nNum = 0;
        colUsed = vector<bool>(col, false);
        diag1 = vector<bool>(2 * col - 1, false);
        diag2 = vector<bool>(2 * col - 1, false);
        dfs(0);
        return nNum;
    }
};

int main() {

    int res = Solution().totalNQueens(8);
    std::cout << res << std::endl;

    return 0;
}