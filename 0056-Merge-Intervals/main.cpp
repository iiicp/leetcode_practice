/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2021/1/1
***********************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    static bool myCompare(const vector<int> &vec1, const vector<int> &vec2) {
        return vec1[0] <= vec2[0];
    }

    bool isCanMerge(vector<int>& v1, vector<int>& v2) {
        if (v1[1] < v2[0])
            return false;
        return true;
    }

public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        int n = intervals.size();
        if (n == 0)
            return res;
        if (n == 1) {
            res.push_back(intervals[0]);
            return res;
        }
        /// 默认排序就可以
        sort(intervals.begin(), intervals.end(), myCompare);

        /// 采用迭代的思维去做，相邻去比较
        int i = 0, j = 1;
        int l = intervals[0][0], r = intervals[0][1];
        while (j < n) {
            auto &v1 = intervals[i];
            auto &v2 = intervals[j];
            if (isCanMerge(v1, v2)) {
                /// 更新右边的值
                r = max(v1[1], v2[1]);
            }else {
                res.push_back({l, r});
                l = v2[0];
                r = v2[1];
            }
            i = j;
            j = j + 1;
        }

        /// 最后i的值
        if (r < intervals[n-1][0])
            return res;
        else {
            vector<int> a = {l, max(r, intervals[n-1][1])};
            res.push_back(a);
            return res;
        }
    }
};

int main(int argc, const char * argv[]) {

    vector<vector<int>> intervals = {
            {1,4},{0,2},{3,5}
    };
    vector<vector<int>> res = Solution().merge(intervals);

    for (auto &vec : res) {
        for (auto &n : vec)
            std::cout << n << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
