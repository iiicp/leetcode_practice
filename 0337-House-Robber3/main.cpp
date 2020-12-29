/***********************************
* File:     main.cpp
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/27
***********************************/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct MyPair{
    TreeNode *node;
    bool use;

    MyPair(TreeNode* node, bool use) {
        this->node = node;
        this->use = use;
    }

    bool operator==(const MyPair& p) const {
        return p.node == node && p.use == use;
    }
};

class MyPairHash {
public:
    size_t operator()(const MyPair& p) const {
        return (size_t)p.node;
    }
};

/// 实现自定义类的hash
/// 需要实现两个函数
/// bool operator==(const MyPair& p) const;
/// size_t operator()(const MyPair& p) const;

/// 注意除了类名外，其它一个不能错
class Solution {
    unordered_map<MyPair, bool, MyPairHash> hash;
    int tryRob(TreeNode *root, int use) {
        if (root == nullptr)
            return 0;
        MyPair p(root, use);
        if (hash.find(p) != hash.end())
            return hash[p];

        int res = tryRob(root->left, true) + tryRob(root->right, true);
        if (use) {
            res += root->val + tryRob(root->left, false) + tryRob(root->right, false);
        }

        hash[p] = res;
        return res;
    }

public:
    int rob(TreeNode* root) {
        return tryRob(root, true);
    }
};

int main() {

    return 0;
}
