/**********************************
 * File:     main.cpp
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/26
 ***********************************/
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
/**
 *  输入：s = "226"
    输出：3
    解释：它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
 */
using namespace std;

class Solution {

  bool isDecode(string &s, int start) {
    if (s.size() - start >= 3) {
      return false;
    }else if (s.size() - start == 2) {
      return (s[start] - '0') * 10 + (s[start + 1] - '0') <= 26;
    }
  }

  /// [start, ...)
  int tryStringIndex(string &s, int start) {
    if (start >= s.size()) {
      return 0;
    }

    if (start == s.size() - 1) {
      return 1 + tryStringIndex(s, start + 1);
    }else {
      int a = (s[start] - '0') * 10 + (s[start + 1] - '0');
      if (a > 26) {
        return 1 + tryStringIndex(s, start + 1) +
               1 + tryStringIndex(s, start + 2);
      }else {

      }
    }
  }
public:
  int numDecodings(string s) {

  }
};

int main() {
  return 0;
}
