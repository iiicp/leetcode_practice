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
  /// 每遍历一个就减去结点的值
  bool hasPathSum(TreeNode* root, int sum) {
    if (root == nullptr)
      return false;

    // 叶子结点判断最终的值
    if (!root->left && !root->right)
      return root->val == sum;

    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
  }

  bool hasPathSum2(TreeNode *root, int sum) {
    if (root == nullptr)
      return false;

    stack<pair<TreeNode*, int>> s;
    s.push(make_pair(root, sum));

    while (!s.empty()) {
      TreeNode *node = s.top().first;
      int num = s.top().second;
      s.pop();

//      std::cout << "< " << node->val << ", " << num << " >" << std::endl;

      if (node->val == num && !node->left && !node->right)
        return true;

      if (node->left)
        s.push(make_pair(node->left, num-node->val));
      if (node->right)
        s.push(make_pair(node->right, num-node->val));
    }

    return false;
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


  std::cout << Solution().hasPathSum2(root, 22) << std::endl;
  return 0;
}