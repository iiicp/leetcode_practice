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
  bool isSymmetric(TreeNode* root) {
    if (root == nullptr)
      return true;

//    root->right = invertBinaryTree(root->right);
//    return isSameTree(root->left, root->right);
    return isMirrorTree(root, root);
  }

  TreeNode *invertBinaryTree(TreeNode *root) {
    if (root == nullptr)
      return root;
    invertBinaryTree(root->left);
    invertBinaryTree(root->right);
    swap(root->left, root->right);
    return root;
  }

  bool isSameTree(TreeNode *l1, TreeNode *l2) {
    if (l1 == nullptr && l2 == nullptr) return true;
    if (!l1 && l2) return false;
    if (l1 && !l2) return false;
    if (l1->val != l2->val) return false;
    return isSameTree(l1->left, l2->left) && isSameTree(l1->right, l2->right);
  }

  bool isMirrorTree(TreeNode *l1, TreeNode *l2) {
    if (l1 == nullptr && l2 == nullptr) return true;
    if (!l1 && l2) return false;
    if (l1 && !l2) return false;
    if (l1->val != l2->val) return false;
    return isMirrorTree(l1->left, l2->right) && isMirrorTree(l1->right, l2->left);
  }

  bool isSymmetric2(TreeNode *root) {
    if (root == nullptr)
      return true;

    stack<TreeNode *> q1, q2;
    q1.push(root);
    q2.push(root);

    while (!q1.empty() && !q2.empty()) {
      TreeNode *n1 = q1.top();
      TreeNode *n2 = q2.top();
      q1.pop();
      q2.pop();

      if (!n1 && n2) return false;
      if (n1 && !n2) return false;

      if (!n1 && !n2) continue;
      if (n1->val != n2->val) return false;

      q1.push(n1->left);
      q1.push(n1->right);
      q2.push(n2->right);
      q2.push(n2->left);
    }

    return q1.empty() && q2.empty();
  }

  bool isSymmetric3(TreeNode *root) {

#if 1
    if (root == nullptr)
      return true;

    stack<TreeNode *> s1;
    s1.push(root);
    s1.push(root);

    while (!s1.empty()) {
      TreeNode *n1 = s1.top();
      s1.pop(); // 要先pop掉
      TreeNode *n2 = s1.top();
      s1.pop();

      if (!n1 && n2) return false;
      if (n1 && !n2) return false;

      if (!n1 && !n2) continue;
      if (n1->val != n2->val) return false;

      s1.push(n1->left);
      s1.push(n2->right);
      s1.push(n1->right);
      s1.push(n2->left);
    }
    return true;
#else
    if(root == NULL)
      return true;

    queue<TreeNode*> q;
    q.push(root);
    q.push(root);
    while(!q.empty()){
      TreeNode* node1 = q.front();
      q.pop();

      TreeNode* node2 = q.front();
      q.pop();

      if(node1 == NULL && node2 == NULL)
        continue;

      if(node1 == NULL || node2 == NULL)
        return false;

      if(node1->val != node2->val)
        return false;

      q.push(node1->left);
      q.push(node2->right);
      q.push(node1->right);
      q.push(node2->left);
    }

    return true;
#endif
  }
};

int main()
{
  /*
 *           1
 *         /   \
 *        2      2
 *       / \    /  \
 *      null 3  null 3
 */

  // [1,2,2,null,3,null,3]
  int arr[] = { 1, 2, 2 , -1, 3, -1,3};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;

  bool res = Solution().isSymmetric3(root);
  std::cout << res << std::endl;


  return 0;
}