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
  bool isBalanced(TreeNode* root) {
    if (root == nullptr)
      return true;
    return (std::abs(height(root->left) - height(root->right)) <= 1) && isBalanced(root->left) && isBalanced(root->right);
  }

  int height(TreeNode *root)
  {
    if (root == nullptr)
      return 0;
    int left = height(root->left);
    int right = height(root->right);
    return std::max(left, right) + 1;
  }

  bool isBalanced2(TreeNode* root) {
    if (root == nullptr)
      return true;
    queue<TreeNode *> q;
    q.push(root);

    unordered_map<TreeNode*, int> hash;

    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();

      int left = 0;
      if (node->left) {
        if (hash.count(node->left))
          left = hash[node->left];
        else {
          left = height(node->left);
          hash[node->left] = left;
        }
      }else {
        left = 0;
      }

      int right = 0;
      if (node->right) {
        if (hash.count(node->right))
          right = hash[node->right];
        else {
          right = height(node->right);
          hash[node->right] = right;
        }
      }else {
        right = 0;
      }

      if (abs(left - right) > 1)
        return false;

      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    return true;
  }
};

int main()
{
  /*
 *           0
 *         /   \
 *        1     2
 *       /  \   /  \
 *      3   5  3   null
 */

  int arr[] = { 0, 1, 2, 3, 5, 3, -1 };
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
  int n1 = sizeof(arr1)/sizeof(int);
  TreeNode *root1 = create_tree(arr1, n1);
  Print(root1);
  std::cout << std::endl;


  std::cout << Solution().isBalanced2(root) << std::endl;
  return 0;
}