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

#include <iostream>
#include <vector>
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
  cout << p->val << ", ";
  Print(p->left);
  Print(p->right);
}

class Solution {
    class STNode {
    public:
        STNode *prev;
        TreeNode *cur;
        int sum;
        STNode() : prev(nullptr), cur(nullptr), sum(0) {}
        STNode(STNode* prev, TreeNode *cur, int sum):  prev(prev), cur(cur), sum(sum) {}
    };
    void findPath(vector<vector<int>> &res, vector<int> &path, TreeNode *root, int tsum, int sum) {
        if (root == nullptr)
            return;
        tsum += root->val;
        path.push_back(root->val);
        if (!root->left && !root->right && tsum == sum) {
            res.push_back(path);
        }else {
            findPath(res, path, root->left, tsum, sum);
            findPath(res, path, root->right,tsum, sum);
        }
        path.pop_back();
        tsum -= root->val;
    }
public:
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> res;
    if (root == nullptr)
        return res;

    vector<int> path;
    findPath(res, path, root, 0, sum);
    return res;
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