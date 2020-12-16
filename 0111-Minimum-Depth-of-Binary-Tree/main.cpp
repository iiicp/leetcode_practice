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
#include <queue>

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
  int minDepth(TreeNode* root) {
    if (root == nullptr)
      return 0;

//    if (!root->left && !root->right)
//      return 1;

    int left = minDepth(root->left);
    int right = minDepth(root->right);

    return std::min(left, right) + 1;
  }


  int minDepth2(TreeNode* root) {
    if (root == nullptr)
      return 0;
    stack<pair<TreeNode *, int>> st;
    st.push(make_pair(root, 1));

    int res = INT_MAX;

    while (!st.empty()) {
      TreeNode *node = st.top().first;
      int level = st.top().second;
      st.pop();

      if (!node->left && !node->right)
        res = std::min(res, level);
      else {
        if (node->left)
          st.push(make_pair(node->left, level+1));
        if (node->right)
          st.push(make_pair(node->right, level+1));
      }
    }
    return res;
  }

  int minDepth3(TreeNode* root) {
    if (root == nullptr)
      return 0;
    queue<pair<TreeNode *, int>> q;
    q.push(make_pair(root, 1));

    while (!q.empty()) {
      TreeNode *node = q.front().first;
      int level = q.front().second;
      q.pop();

      if(!node->left && !node->right)
        return level;
      else {
        if (node->left)
          q.push(make_pair(node->left, level+1));
        if (node->right)
          q.push(make_pair(node->right, level+1));
      }
    }
    return 0;
  }
};

int main()
{
  /*
 *           0
 *         /   \
 *        1     2
 *             /  \
 *             3   null
 */

  int arr[] = { 0, 1, 2, -1, -1, 3, -1 };
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);

  int res = Solution().minDepth(root);
  std::cout << res << std::endl;

  res = Solution().minDepth2(root);
  std::cout << res << std::endl;

  res = Solution().minDepth3(root);
  std::cout << res << std::endl;

  return 0;
}