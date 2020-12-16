/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/16
 ***********************************/

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    assert(k <= nums.size());

    // 统计每个数出现的频率
    unordered_map<int, int> hashmap;
    for (int i = 0; i < nums.size(); ++i) {
      hashmap[nums[i]]++;
    }

    // 遍历维护一个大小为k的最小堆
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for (unordered_map<int, int>::iterator iter = hashmap.begin();  iter != hashmap.end() ; ++iter) {
      if (pq.size() == k) {
        if (iter->second > pq.top().first) {
          pq.pop();
          pq.push(make_pair(iter->second, iter->first));
        }
      }else {
        pq.push(make_pair(iter->second, iter->first));
      }
    }

    vector<int> res;
    while (!pq.empty()) {
      res.push_back(pq.top().second);
      pq.pop();
    }
    return res;
  }
};

/*
 *  输入: nums = [1,1,1,2,2,3], k = 2
    输出: [1,2]

    输入: nums = [1], k = 1
    输出: [1]
 */
int main() {

  vector<int> nums = {1};
  vector<int> res = Solution().topKFrequent(nums, 1);
  for (auto &x : res)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;
}