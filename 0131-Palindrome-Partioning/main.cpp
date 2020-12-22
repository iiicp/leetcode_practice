/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/22
 ***********************************/
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
  bool isPalind(string &str, int l, int r) {
    while (l <= r) {
      if (str[l] != str[r]) {
        return false;
      }
      l++;
      r--;
    }
    return true;
  }

  void findPalindrome(string &s, int l, vector<string> &vec, vector<vector<string>> &res) {
    if (l == s.size()) {
      res.push_back(vec);
      return;
    }
    // 每一次的候选集
    for (int r = l; r < s.size(); ++r) {
      // 每次的逻辑处理，先试错当前的串
      if (isPalind(s, l, r)) {
        vec.push_back(s.substr(l, r - l + 1));
        findPalindrome(s, r + 1, vec, res);
        vec.pop_back();
      }
    }
  }
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    if (s.size() == 0)
      return res;
    vector<string> vec;
    findPalindrome(s, 0, vec, res);
    return res;
  }
};

int main() {

  vector<vector<string>> res = Solution().partition("aaba");
  for (auto &vec: res) {
    std::cout << "[";
    for (auto &str : vec) {
      std::cout << str << " ";
    }
    std::cout << "]" << std::endl;
  }

  return 0;
}