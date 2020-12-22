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
  void findIpAddresses(string &s, int start, string path, int segment, int dotCnt, vector<string> &res) {
    if (dotCnt > 3) {
      return;
    }
    if (start == s.size() - 1 && dotCnt != 3) {
      return;
    }
    if (start == s.size() - 1 && dotCnt == 3) {
      path += s[start];
      segment = segment * 10 + s[start] - '0';
      if (segment <= 255) {
        res.push_back(path);
      }
      return;
    }

    if ((segment * 10 + s[start] - '0') > 255)
      return;

    if (segment == 0 && s[start] == '0') {
      findIpAddresses(s, start + 1, path + s[start] + ".", 0, dotCnt + 1, res);
    }else {
      findIpAddresses(s, start + 1, path + s[start],segment * 10 + s[start] - '0', dotCnt, res);
      findIpAddresses(s, start + 1, path + s[start] + ".", 0,dotCnt + 1, res);
    }
  }
public:
  vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    if (s.size() == 0)
      return res;
    findIpAddresses(s, 0, "", 0, 0, res);
    return res;
  }
};

int main() {
  vector<string> testSet = {"25525511135", "0000", "1111", "101023"};

  for (auto &str : testSet) {
    vector<string> res = Solution().restoreIpAddresses(str);
    std::cout << "input: " << str << std::endl;
    for (auto &str : res)
      std::cout << str << std::endl;

    std::cout << std::endl;
  }

  return 0;
}