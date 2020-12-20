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
    bool isValidBST(TreeNode* root) {
        if (root == nullptr)
            return true;

        if (!root->left && !root->right) {
            return true;
        }

        long leftMax = findMaxValue(root->left);
        long rightMin = findMinValue(root->right);
        std::cout << "( " << leftMax << ", " << rightMin << " )" << std::endl;
        return leftMax < root->val && rightMin > root->val
        && isValidBST(root->left) && isValidBST(root->right);
    }

    long findMaxValue(TreeNode *root) {
        if (root == nullptr)
            return LONG_MIN;
        long leftMax = findMaxValue(root->left);
        long rightMax = findMaxValue(root->right);
        long maxValue;
        if (leftMax > rightMax) {
            maxValue = leftMax;
        }else {
            maxValue = rightMax;
        }
        if (maxValue < root->val)
            maxValue = root->val;
        return maxValue;
    }

    long findMinValue(TreeNode *root) {
        if (root == nullptr)
            return LONG_MAX;
        long leftMin = findMinValue(root->left);
        long rightMin = findMinValue(root->right);
        long minValue;
        if (leftMin < rightMin) {
            minValue = leftMin;
        }else {
            minValue = rightMin;
        }
        if (minValue > root->val)
            minValue = root->val;
        return minValue;
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
 *    1   3  null null     null null null 10
 */

  // [5,4,8,11,null,13,4,7,2,null,null,null,1]
  // 22
  int arr[] = { 5,4,8,2,-1,6,9, 1,3,-1,-1,-1,-1,-1,10};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;

  std::cout << Solution().isValidBST(root) << std::endl;

  return 0;
}