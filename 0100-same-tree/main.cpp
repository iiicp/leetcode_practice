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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        string s1 = "#";
        string s2 = "#";
        genString(p, s1);
        std::cout << s1 << std::endl;
        genString(q,s2);
        std::cout << s2 << std::endl;

        return s1 == s2;
    }

    bool isSameTree2(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if (!p && q) return false;
        if (p && !q) return false;
        if (p->val == q->val) return true;

        return isSameTree2(p->left, q->left) && isSameTree2(p->right, q->right);
    }

    bool isSameTree3(TreeNode* p, TreeNode* q) {

        stack<TreeNode*> s1, s2;
        s1.push(p);
        s2.push(q);

        while (!s1.empty() && !s2.empty()) {
            TreeNode *n1 = s1.top();
            TreeNode *n2 = s2.top();
            s1.pop();
            s2.pop();

            if (!n1 && n2) return false;
            if (n1 && !n2) return false;
            if (!n1 && !n2) continue;

            if (n1->val != n2->val) return false;

            s1.push(n1->left);
            s1.push(n1->right);
            s2.push(n2->left);
            s2.push(n2->right);
        }

        return s1.empty() && s2.empty();
    }

    bool isSameTree4(TreeNode* p, TreeNode* q) {

        queue<TreeNode *> q1, q2;
        q1.push(p);
        q2.push(q);

        while (!q1.empty() && !q2.empty()) {
            TreeNode *n1 = q1.front();
            TreeNode *n2 = q2.front();
            q1.pop();
            q2.pop();

            if (!n1 && n2) return false;
            if (n1 && !n2) return false;
            if (!n1 && !n2) continue;
            if (n1->val != n2->val) return false;

            q1.push(n1->left);
            q1.push(n1->right);

            q2.push(n2->left);
            q2.push(n2->right);
        }

        return q1.empty() && q2.empty();
    }

    void genString(TreeNode* p, string &str) {
        if (p == nullptr) {
            str += "null#";
            return;
        }

        str += to_string(p->val) + "#";

        genString(p->left, str);
        genString(p->right, str);
    }
};

int main()
{
  /*
 *           0
 *         /   \
 *        1     2
 *             /  \
 *             3   null
 */

  int arr[] = { 0, 1, 2, -1, -1, 3, -1 };
  int n = sizeof(arr)/sizeof(int);
  TreeNode *root = create_tree(arr, n);
  Print(root);
  std::cout << std::endl;

  int arr1[] = { 0, 1, 2, -1, -1, 3, -1 };
  int n1 = sizeof(arr1)/sizeof(int);
  TreeNode *root1 = create_tree(arr1, n1);
  Print(root1);
  std::cout << std::endl;

  bool res = Solution().isSameTree(root, root1);
  std::cout << res << std::endl;

  res = Solution().isSameTree2(root, root1);
  std::cout << res << std::endl;

    res = Solution().isSameTree3(root, root1);
    std::cout << res << std::endl;

    res = Solution().isSameTree4(root, root1);
    std::cout << res << std::endl;

  return 0;
}