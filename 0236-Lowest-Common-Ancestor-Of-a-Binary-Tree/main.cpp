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

    bool findNode(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) {
            return false;
        }
        if (root == p || root == q)
            return true;
        return findNode(root->left, p, q) || findNode(root->right, p, q);
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
            return root;

        bool res1 = findNode(root->left, p, q);
        bool res2 = findNode(root->right, p, q);

        if (res1 && res2) {
            return root;
        }else if (res1){
            return lowestCommonAncestor(root->left, p, q);
        }else {
            return lowestCommonAncestor(root->right, p, q);
        }
    }

    TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
            return root;

        TreeNode *leftNode = lowestCommonAncestor2(root->left, p, q);
        TreeNode *rightNode = lowestCommonAncestor2(root->right, p, q);

        if (leftNode && rightNode) {
            return root;
        }else if (leftNode) {
            return leftNode;
        }else if (rightNode) {
            return rightNode;
        }else {
            return nullptr;
        }
    }
};

int main()
{
  /*
 *             5
 *          /                 \
 *        4                    8
 *       /  \                 /  \
 *      2   null           6   9
 *    1   3  null null     null null null 1
 */

  // [5,4,8,11,null,13,4,7,2,null,null,null,1]
  // 22
  int arr[] = { 5,4,8,2,-1,6,9, 1,3,-1,-1,-1,-1,-1,1};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;

  TreeNode *node = Solution().lowestCommonAncestor(root, root->left->left, root->left);
  if (node) {
      std::cout << node->val << std::endl;
  }else {
      std::cout << "null" << std::endl;
  }

    node = Solution().lowestCommonAncestor2(root, root->left->left, root->right);
    if (node) {
        std::cout << node->val << std::endl;
    }else {
        std::cout << "null" << std::endl;
    }

  return 0;
}