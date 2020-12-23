/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/23
 ***********************************/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
  string genTimeStr(int minus) {
    if (minus == 60) {
      std::cout << std::endl;
    }
    int hours = minus / 60;
    int mis = minus % 60;
    string res;
    res += to_string(hours);
    if (mis < 10) {
      res += ":0";
      res += to_string(mis);
    }else {
      res += ":" + to_string(mis);
    }
    return res;
  }
  void dfs(vector<int>& candidate, int num, int start, int selectMinusTotal, int AllMinus, vector<string> &res) {
    if (num == 0) {
      res.push_back(genTimeStr(AllMinus));
      return;
    }
    for (int i = start; i < candidate.size(); ++i) {
      if (AllMinus + candidate[i] > 11 * 60 + 59) {
        continue;
      }
      if (i <= 5 && selectMinusTotal + candidate[i] >= 60) {
        continue;
      }
      dfs(candidate, num - 1, i + 1, selectMinusTotal + candidate[i], AllMinus + candidate[i], res);
    }
  }
public:
  vector<string> readBinaryWatch(int num) {
    vector<string> res;
    vector<int> candidate{1,2,4,8,16,32,60,120,240,480};
    vector<int> selectMinusN;
    dfs(candidate, num, 0, 0, 0, res);
    return res;
  }
};

/**
 *  二进制手表顶部有 4 个 LED 代表 小时（0-11），底部的 6 个 LED 代表 分钟（0-59）
 *
 *  输入: n = 1
    返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
    输出的顺序没有要求。
    小时不会以零开头，比如 “01:00” 是不允许的，应为 “1:00”。
    分钟必须由两位数组成，可能会以零开头，比如 “10:2” 是无效的，应为 “10:02”。
    超过表示范围（小时 0-11，分钟 0-59）的数据将会被舍弃，也就是说不会出现 "13:00", "0:61" 等时间。
 */

int main() {

  vector<string> res = Solution().readBinaryWatch(4);
  sort(res.begin(), res.end());
  std::cout << res.size() << std::endl;
  std::cout << "[";
  for (auto &s : res)
    std::cout << s << " ";
  std::cout << std::endl;
  return 0;
}
