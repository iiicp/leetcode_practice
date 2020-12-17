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
#include <string>
#include <unordered_map>

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
  int sumOfLeftLeaves(TreeNode* root) {
    if (root == nullptr)
      return 0;

    queue<pair<TreeNode*, bool>> q;
    q.push(make_pair(root, false));
    int sum = 0;
    while (!q.empty()) {
      TreeNode *node = q.front().first;
      bool isLeft = q.front().second;
      q.pop();

      if (isLeft && !node->left && !node->right)
        sum += node->val;

      if (node->left)
        q.push(make_pair(node->left, true));
      if (node->right)
        q.push(make_pair(node->right, false));
    }

    return sum;
  }

  int sumOfLeftLeaves2(TreeNode* root) {
    if (root == nullptr)
      return 0;

    return _sumOfLeftLeaves(root, false);
  }

  int _sumOfLeftLeaves(TreeNode* root, bool isLeft) {
    if (root == nullptr)
      return 0;

    if (!root->left && !root->right && isLeft)
      return root->val;

    return _sumOfLeftLeaves(root->left, true) +
           _sumOfLeftLeaves(root->right, false);
  }
};

int main()
{
  /*
 *             5
 *          /                 \
 *        4                    8
 *       /  \                 /  \
 *      11   null           13   4
 *    7   2  null null     null null null 1
 */

  // [5,4,8,11,null,13,4,7,2,null,null,null,1]
  // 22
  int arr[] = { 5,4,8,11,-1,13,4, 7,2,-1,-1,-1,-1,-1,1};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
  int n1 = sizeof(arr1)/sizeof(int);
  TreeNode *root1 = create_tree(arr1, n1);
  Print(root1);
  std::cout << std::endl;

  std::cout << Solution().sumOfLeftLeaves(root) << std::endl;

  std::cout << Solution().sumOfLeftLeaves2(root) << std::endl;

  return 0;
}