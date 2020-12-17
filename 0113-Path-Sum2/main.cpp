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
  cout << p->val << ", ";
  Print(p->left);
  Print(p->right);
}

class Solution {
public:
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> res;
    if (root == nullptr)
      return res;
    vector<int> path;
    dfs(root,sum,path,0,res);
    return res;
  }

  void dfs(TreeNode *root, int sum, vector<int>& path, int tsum, vector<vector<int>> &res) {
    path.push_back(root->val);
    tsum += root->val;
    // 递归终止条件
    if (tsum == sum && !root->left && !root->right) {
      res.push_back(path);
    }else {
      if (root->left)
        dfs(root->left, sum, path, tsum, res);
      if (root->right)
        dfs(root->right, sum, path, tsum, res);
    }
    // 递归终止之后回溯
    path.pop_back();
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

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;


  vector<vector<int>> res = Solution().pathSum(root,22);
  for (auto &v : res) {
    for (auto &n : v) {
      std::cout << n << ", ";
    }
    std::cout << std::endl;
  }
  return 0;
}