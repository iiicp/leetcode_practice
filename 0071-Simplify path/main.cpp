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
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
  string simplifyPath(string path) {
    vector<string> v;
    int start = 1, i = 1;
    while (i <= path.size()) {
      if (i == path.size() || path[i] == '/') {
        string f = path.substr(start, i - start);
        if (f.size() > 0) {
          if (f == "..") {
            if (v.size() > 0) {
              v.pop_back();
            }
          }else if (f != ".") {
            v.push_back(f);
          }
        }
        start = i + 1;
      }
      i++;
    }
    string res;
    for (auto &s : v)
      res += "/" + s;

    return res == "" ? "/" : res;
  }
};

/*
 * 输入："/home/"
   输出："/home"

   输入："/../"
   输出："/"

   输入："/home//foo/"
   输出："/home/foo"

   输入："/a/./b/../../c/"
   输出："/c"

   输入："/a/../../b/../c//.//"
   输出："/c"

   输入："/a//b////c/d//././/.."
   输出："/a/b/c"
 */

int main() {

  string path = Solution().simplifyPath("/../");
  std::cout << path << std::endl;

  return 0;
}