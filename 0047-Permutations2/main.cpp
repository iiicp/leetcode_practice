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

using namespace std;

class Solution {
  vector<bool> visited;
  void dfs(vector<int> &nums, int index, vector<int> &path, vector<vector<int>> &res) {
    if (index == nums.size()) {
      res.push_back(path);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (!visited[i]) {

        if (i > 0 && nums[i] == nums[i-1] && !visited[i-1])
          continue;
        visited[i] = true;
        path.push_back(nums[i]);
        dfs(nums, index + 1, path, res);
        path.pop_back();
        visited[i] = false;
      }
    }
  }
public:
  // 数字可重复
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() == 0)
      return res;
    vector<int> path;
    visited.clear();
    visited = vector<bool>(nums.size(), false);
    dfs(nums, 0, path, res);
    return res;
  }

};

int main() {
  // [0,-1,1]
  // -10 ~ 10
  vector<int> nums{0,1,1};
  vector<vector<int>> res = Solution().permuteUnique(nums);
  for (auto &v : res) {
    std::cout << "[";
    for (auto n : v) {
      std::cout << n << " ";
    }
    std::cout << "]" << endl;
  }
  return 0;
}