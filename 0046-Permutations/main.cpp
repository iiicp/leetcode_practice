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
#include <iostream>
#include <unordered_map>

using namespace std;


class Solution {

  vector<bool> visit;

  void dfs(vector<int> &nums, int index, vector<int> &path, vector<vector<int>> &res) {
    if (index == nums.size()) {
      res.push_back(path);
      return;
    }

    // 每次的候选集是所有的数字
    for (int i = 0; i < nums.size(); ++i) {
      if (!visit[i]) {
        visit[i] = true;
        path.push_back(nums[i]);
        dfs(nums, index + 1, path, res);
        path.pop_back();
        visit[i] = false;
      }
    }
  }
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() == 0)
      return res;
    visit.clear();
    visit = vector<bool>(nums.size(), false);
    vector<int> path;
    dfs(nums, 0, path, res);
    return res;
  }
};

int main() {
  // [0,-1,1]
  vector<int> nums{0,-1,1};
  vector<vector<int>> res = Solution().permute(nums);
  for (auto &v : res) {
    std::cout << "[";
    for (auto n : v) {
      std::cout << n << " ";
    }
    std::cout << "]" << endl;
  }
  return 0;
}