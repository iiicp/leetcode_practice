/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/15
 ***********************************/

#include <queue>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
class Solution {
public:
    /// 建模成一个图形问题，顶点表示为数字，边表示为数字之间可以通过一个完全平方数来转换
    /// 问题就变成了，图论里面的最短路径
    int numSquares(int n) {

        assert(n > 0);

        queue<pair<int, int>> q;
        q.push(make_pair(n, 0));

        vector<bool> visited(n+1, false);
        visited[n] = true;

        while (!q.empty()) {
            int num = q.front().first;
            int level = q.front().second;
            q.pop();

            if (num == 0)
                return level;

            int i = 1;
            int c;
            while (true) {
                c = num - i * i;
                if (c < 0) break;
                if (c == 0)
                    return level+1;
                if (!visited[c]) {
                    q.push(make_pair(c, level + 1));
                    visited[c] = true;
                }
                i++;
            }
        }

        return 0;
    }
};

int main(){

    int res = Solution().numSquares(13);
    std::cout << res << std::endl;

    return 0;
}