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
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
  unordered_map<int, string> dict;
  // 从start处开始找数字字符串的组合
  void findCombinations(string &digits, int start, string path, vector<string> &res) {
    if (start == digits.size()) {
      res.push_back(path);
      return;
    }
    char c = digits[start];
    string str = dict[c - '0'];
    for (int i = 0; i < str.size(); ++i) {
      findCombinations(digits, start + 1, path + str[i], res);
    }
  }
public:
  vector<string> letterCombinations(string digits) {
    dict = {
        {2, "abc"},
        {3, "def"},
        {4, "ghi"},
        {5, "jkl"},
        {6, "mno"},
        {7, "pqrs"},
        {8, "tuv"},
        {9, "wxyz"}
    };

    vector<string> res;
    if (digits.size() == 0)
      return res;
    findCombinations(digits, 0, "", res);
    return res;
  }
};

int main() {

  vector<string> res = Solution().letterCombinations("");
  for (auto &str : res)
    std::cout << str << std::endl;

  return 0;
}