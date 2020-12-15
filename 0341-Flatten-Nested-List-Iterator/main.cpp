/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/15
 ***********************************/

#include <vector>

using namespace std;

 // This is the interface that allows for creating nested lists.
 // You should not implement it, or speculate about its implementation
class NestedInteger {
  public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
  vector<int> data;
  int i;
public:
  NestedIterator(vector<NestedInteger> &nestedList) {
    dfs(nestedList, data);
    i = 0;
  }

  int next() {
    return data[i++];
  }

  bool hasNext() {
    if (i < data.size()) {
      return true;
    }
    return false;
  }

  void dfs(const vector<NestedInteger> &nestedList, vector<int> &data) {
    for (auto &n : nestedList) {
      if (n.isInteger()){
        data.push_back(n.getInteger());
      }else {
        dfs(n.getList(), data);
      }
    }
  }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

int main() {

  return 0;
}