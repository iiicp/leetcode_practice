/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/16
 ***********************************/

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *createList(int *arr, int len) {
  if (len == 0)
    return nullptr;

  ListNode *root = new ListNode(arr[0]);
  ListNode *p = root;
  for (int i = 1; i < len; ++i) {
    ListNode *q = new ListNode(arr[i]);
    p->next = q;
    p = q;
  }
  return root;
}

void printList(ListNode *node) {
  while (node) {
    std::cout << node->val << ", ";
    node = node->next;
  }
  std::cout << std::endl;
}

class CompareListNode {
public:
  bool operator()(ListNode *lst1, ListNode *lst2) {
    return lst1->val > lst2->val;
  }
};

class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {

    // 第三个参数，传递仿函数对象(重载了operator()的类)
    priority_queue<ListNode*, vector<ListNode *>, CompareListNode> pq;

    /// 将队头都入队到优先级队列里面
    for (auto &node : lists) {
      if (node) {
        pq.push(node);
      }
    }

    ListNode dummyHead(-1);
    ListNode *cur = &dummyHead;

    while (!pq.empty()) {
      ListNode *nextNode = pq.top();
      pq.pop();

      cur->next = nextNode;
      cur = cur->next;

      if (nextNode->next) {
        pq.push(nextNode->next);
      }
    }

    return dummyHead.next;
  }
};

/*
 *  输入: nums = [1,1,1,2,2,3], k = 2
    输出: [1,2]

    输入: nums = [1], k = 1
    输出: [1]
 */
int main() {

  int arr1[] = {1,2,3};
  int arr2[] = {2,4,6};
  int arr3[] = {3,4,9};
  ListNode *head1 = createList(arr1, sizeof(arr1)/sizeof(int));
  printList(head1);
  ListNode *head2 = createList(arr2, sizeof(arr2)/sizeof(int));
  printList(head2);
  ListNode *head3 = createList(arr3, sizeof(arr3)/sizeof(int));
  printList(head3);
  vector<ListNode *> v = {head1, head2, head3};
  ListNode *root = Solution().mergeKLists(v);
  printList(root);

  return 0;
}