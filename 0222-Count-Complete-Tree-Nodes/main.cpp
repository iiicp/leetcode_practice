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
  int countNodes(TreeNode* root) {
    if (root == nullptr)
      return 0;
    int num = 0;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();
      num++;
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    return num;
  }

  int countNodes_recur(TreeNode *root) {
    int num = 0;
    _countNodes(root, num);
    return num;
  }
  void _countNodes(TreeNode* root, int &num) {
    if (root == nullptr)
      return;
    num++;
    _countNodes(root->left, num);
    _countNodes(root->right, num);
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

  int num = Solution().countNodes(root);
  std::cout << num << std::endl;

  num = Solution().countNodes_recur(root);
  std::cout << num << std::endl;

  return 0;
}