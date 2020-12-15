/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/15
 ***********************************/

#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (root == nullptr)
            return res;
        vector<vector<int>> temp;

        queue<pair<TreeNode *, int>> q;
        q.push(make_pair(root, 0));

        while (!q.empty()) {
            TreeNode *node = q.front().first;
            int level = q.front().second;
            q.pop();

            if (level == temp.size())
                temp.push_back(vector<int>());

            if (temp[level].size() == 0)
                temp[level].push_back(node->val);
            else
                temp[level][0] = (node->val);

            if (node->left)
                q.push(make_pair(node->left, level + 1));

            if (node->right)
                q.push(make_pair(node->right, level + 1));
        }

        for (int i = 0; i < temp.size(); ++i) {
            res.push_back(temp[i][0]);
        }
        return res;
    }
};

int main()
{
    return 0;
}