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
#include <iostream>

using namespace std;

class Solution {
  void dfs(vector<int>& nums, int start, vector<int> &cur_path, vector<vector<int>> &res) {
    res.push_back(cur_path);
    for (int i = start; i < nums.size(); ++i) {
      if (i > start && nums[i] == nums[i-1])
        continue;
      cur_path.push_back(nums[i]);
      dfs(nums, i + 1, cur_path, res);
      cur_path.pop_back();
    }
  }
public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() == 0)
      return res;
    sort(nums.begin(), nums.end());
    vector<int> path;
    dfs(nums, 0, path, res);
    return res;
  }
};

int main() {

  vector<int> nums = {1,2,2};
  vector<vector<int>> res = Solution().subsetsWithDup(nums);
  for (auto &v : res) {
    std::cout << "[";
    for (auto &n : v) {
      std::cout << n  << " ";
    }
    std::cout << "]" << std::endl;
  }

  return 0;
}