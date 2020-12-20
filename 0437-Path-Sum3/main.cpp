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

  if (index >= len || arr[index] == -100) {
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
    void findPath(vector<vector<int>> &res, vector<int> &path, TreeNode *root, int sum) {
        if (root == nullptr)
            return;

        path.push_back(root->val);

        /*
         *  遇到一个解，保存起来，我们仍然还要继续往下走
         */
        if (root->val == sum) {
            res.push_back(path);
            std::cout << "( ";
            for (auto v : path)
                std::cout << v << ", ";
            std::cout << ")" << std::endl;
        }

        findPath(res, path, root->left, sum - root->val);
        findPath(res, path, root->right, sum - root->val);

        path.pop_back();
    }

    int findPath2(TreeNode *root, int sum) {
        if (root == nullptr)
            return 0;

        /**
         * 遇到一个解，保存起来，同时继续往下走
         */
        int res = 0;
        if (root->val == sum) {
            res += 1;
        }
        return findPath2(root->left, sum - root->val) +
        findPath2(root->right, sum - root->val) + res;
    }

    vector<vector<int>> res;

public:
  int pathSum(TreeNode* root, int sum) {

    if (root == nullptr)
        return 0;

#if 1
    vector<int> path;
    findPath(res, path, root, sum);

    pathSum(root->left, sum);
    pathSum(root->right, sum);
#else
    int res = findPath2(root, sum);
    return pathSum(root->left, sum) + pathSum(root->right, sum) + res;
#endif
    return 0;
  }
};

int main()
{
  /*
 *                  1
 *          /                 \
 *        -2                    -3
 *       /  \                     /  \
 *      1       3               -2    null
 *    -1   null  null null     null null null null
 */

  // [5,4,8,11,null,13,4,7,2,null,null,null,1]
  // 22
  int arr[] = { 1,-2,-3,1,3,-2,-100,-1,-100,-100,-100,-100,-100,-100,-100};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;


  int res = Solution().pathSum(root,-1);
  std::cout << res << std::endl;
  return 0;
}