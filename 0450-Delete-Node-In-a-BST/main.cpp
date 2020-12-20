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
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr)
            return root;
        TreeNode *cur = root;
        TreeNode *prev = nullptr;
        bool isLeft = true;
        while (cur) {
            if (key == cur->val) {
                break;
            }else if (key < cur->val) {
                prev = cur;
                isLeft = true;
                cur = cur->left;
            }else if (key > cur->val) {
                prev = cur;
                isLeft = false;
                cur = cur->right;
            }
        }

        if (cur == nullptr)
            return root;

        if (cur->right) {
            TreeNode *rightMin = cur->right;
            prev = cur;
            isLeft = false;
            while (rightMin->left) {
                isLeft = true;
                prev = rightMin;
                rightMin = rightMin->left;
            }
            if (isLeft)
                prev->left = nullptr;
            else {
                prev->right = nullptr;
            }
            int t = cur->val;
            cur->val = rightMin->val;
            rightMin->val = t;
            delete rightMin;
        }else if (cur->left){
            TreeNode *leftMax = cur->left;
            prev = cur;
            isLeft = true;
            while (leftMax->right) {
                isLeft = false;
                prev = leftMax;
                leftMax = leftMax->right;
            }
            if (isLeft)
                prev->left = nullptr;
            else {
                prev->right = nullptr;
            }
            int t = cur->val;
            cur->val = leftMax->val;
            leftMax->val = t;
            delete leftMax;
        }else {
            if (cur == root) {
                root = nullptr;
            }else {
                if (isLeft) {
                    prev->left = nullptr;
                }else {
                    prev->right = nullptr;
                }
            }
            delete cur;
        }

        return root;
    }
};

int main()
{
  /*
 *             5
 *          /                 \
 *        3                    6
 *       /  \                 /  \
 *      2     4               null   7
 *    null  null   null null     null null null null
 */

  // [5,4,8,11,null,13,4,7,2,null,null,null,1]
  // 22
  int arr[] = { 5,3,6,2,4,-1,7, -1,-1,-1,-1,-1,-1,-1,-1};
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

//  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
//  int n1 = sizeof(arr1)/sizeof(int);
//  TreeNode *root1 = create_tree(arr1, n1);
//  Print(root1);
//  std::cout << std::endl;

  root = Solution().deleteNode(root, 5);
Print(root);
std::cout << std::endl;


  return 0;
}