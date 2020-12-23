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
    // 不选择当前元素的结果
    res.push_back(cur_path);

    // 选择当前元素的结果
    for (int i = start; i < nums.size(); ++i) {
      cur_path.push_back(nums[i]);
      dfs(nums, i + 1, cur_path, res);
      cur_path.pop_back();
    }
  }
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() == 0)
      return res;
    vector<int> path;
    sort(nums.begin(), nums.end());
    dfs(nums, 0, path, res);
    return res;
  }
};

int main() {

  vector<int> nums = {1,2,3};
  vector<vector<int>> res = Solution().subsets(nums);
  for (auto &v : res) {
    std::cout << "[";
    for (auto &n : v) {
      std::cout << n  << " ";
    }
    std::cout << "]" << std::endl;
  }

  return 0;
}