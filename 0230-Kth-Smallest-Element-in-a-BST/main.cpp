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
  Print(p->left);
  cout << p->val << ", ";
  Print(p->right);
}

class Solution {
    void InOrder(TreeNode *root, vector<int> &res, int k) {
        if (root == nullptr || res.size() == k)
            return;
        InOrder(root->left, res, k);
        res.push_back(root->val);
        InOrder(root->right, res, k);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> res;
        InOrder(root, res, k);
        assert(res.size() >= k);
        return res[k-1];
    }
};

int main()
{
  /*
 *             50
 *          /                 \
 *        30                   70
 *       /  \                 /  \
 *      null  40             60   80
 *    null  null   null null     null null null null
 */

  // [5,4,8,11,null,13,4,7,2,null,null,null,1]
  // 22
  int arr[] = { 50,30,70,-1,40,60, 80};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;

  int res = Solution().kthSmallest(root, 2);
  std::cout << res << std::endl;

  return 0;
}