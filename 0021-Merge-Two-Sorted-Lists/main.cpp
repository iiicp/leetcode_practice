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

class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummyHead(-1);
    ListNode *p = &dummyHead;

    ListNode *p1 = l1, *p2 = l2;
    while (p1 || p2) {
      int a = p1 ? p1->val : INT_MAX;
      int b = p2 ? p2->val : INT_MAX;
      if (a < b) {
        p->next = p1;
        p1 = p1 ? p1->next : nullptr;
      }else {
        p->next = p2;
        p2 = p2 ? p2->next : nullptr;
      }
      p = p->next;
    }

    return dummyHead.next;
  }
};

int main() {

  int arr1[] = {1,2,3};
  int arr2[] = {2,4,6};
  ListNode *head1 = createList(arr1, sizeof(arr1)/sizeof(int));
  printList(head1);
  ListNode *head2 = createList(arr2, sizeof(arr2)/sizeof(int));
  printList(head2);
  ListNode *root = Solution().mergeTwoLists(head1, head2);
  printList(root);

  return 0;
}