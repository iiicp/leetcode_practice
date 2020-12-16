/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/16
 ***********************************/
 
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


/**
*  重点设计：返回树的跟结点
*/
void _recurseve(TreeNode* &root, int *arr, int len, int index) {

  if (index >= len || arr[index] == -1) {
    return;
  }
  // -1 mean null node
  root = new TreeNode(arr[index]);
  _recurseve(root->left, arr, len, 2 * index + 1);
  _recurseve(root->right, arr, len, 2 * index + 2);
}

TreeNode *create_tree(int *arr, int len) {
  TreeNode *root = nullptr;
  _recurseve(root, arr, len, 0);
  return root;
}

void Print(TreeNode* p) {
  if (NULL == p)
    return;
  cout << p->val;
  Print(p->left);
  Print(p->right);
}

class Solution {
public:
  int maxDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);

    return std::max(left, right) + 1;
  }

  /// using stack
  /// 遇到叶子节点的时候，去更新最大深度
  int maxDepth2(TreeNode *root) {
    if (root == nullptr)
      return 0;

    stack<pair<TreeNode *, int>> st;
    st.push(make_pair(root, 1));

    int res = 0;
    while (!st.empty()) {
      TreeNode *node = st.top().first;
      int level = st.top().second;
      st.pop();

      if (!node->left && !node->right)
        res = std::max(res, level);
      else {
        if (node->left)
          st.push(make_pair(node->left, level+1));
        if (node->right)
          st.push(make_pair(node->right, level+1));
      }
    }

    return res;
  }
};

int main()
{
  /*
 *           0
 *         /   \
 *        null  2
 *             /  \
 *             3   null
 */

  int arr[] = { 0, -1, 2, -1, -1, 3, -1 };
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);

  int res = Solution().maxDepth(root);
  std::cout << res << std::endl;

  res = Solution().maxDepth2(root);
  std::cout << res << std::endl;

  return 0;
}