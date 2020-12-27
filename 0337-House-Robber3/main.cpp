/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/27
***********************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int rob(TreeNode* root) {
        if (root == nullptr)
            return 0;

        /// 先通过层序遍历将数据线性化
        vector<int> nums;
        queue<pair<TreeNode *, int>> q;
        q.push(make_pair(root, 0));

        while (!q.empty()) {
            TreeNode *node = q.front().first;
            int level = q.front().second;
            q.pop();
            if (nums.size() == level) {
                nums.push_back(0);
            }

            nums[level] += node->val;

            if (node->left) {
                q.push(make_pair(node->left, level + 1));
            }
            if (node->right) {
                q.push(make_pair(node->right, level + 1));
            }
        }

        /// 动态规划思路
        /// 状态定义：考虑[0, index]区间
        int dp_n_2 = 0;
        int dp_n_1 = nums[0];
        int cur = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            cur = std::max(dp_n_1, nums[i] + dp_n_2);
            dp_n_2 = dp_n_1;
            dp_n_1 = cur;
        }
        return cur;
    }
};

int main() {

    return 0;
}
