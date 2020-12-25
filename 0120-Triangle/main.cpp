/**********************************
 * File:     main.cpp
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/25
 ***********************************/
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

class Solution {
  int maxRow;
  int diretion[2][2] = {{1, 0}, {1, 1}};
  bool inTriangle(int x, int y) {
    return x >= 0 && x < maxRow && y >= 0 && y < maxRow;
  }
  vector<vector<int>> memo;
  /// 递归解法
  int tryElement(vector<vector<int>>& triangle, int x, int y) {
    if (!inTriangle(x, y))
      return 0;
    return triangle[x][y] + std::min(tryElement(triangle,x + diretion[0][0], y + diretion[0][1]),
                                     tryElement(triangle,x + diretion[1][0], y + diretion[1][1]));
  }

  /// 记忆化方法
  int tryElement2(vector<vector<int>>& triangle, int x, int y) {
    if (!inTriangle(x, y))
      return 0;

    pair<int,int> newPoint1 = make_pair(x + diretion[0][0], y + diretion[0][1]);
    pair<int,int> newPoint2 = make_pair(x + diretion[1][0], y + diretion[1][1]);

//    std::cout << "newPoint1: " << "{ " << newPoint1.first << ", " << newPoint1.second << "}" << std::endl;
//    std::cout << "newPoint2: " << "{ " << newPoint2.first << ", " << newPoint2.second << "}" << std::endl;
//    std::cout << endl;

    int a = 0, b = 0;
    if (inTriangle(newPoint1.first, newPoint1.second)) {
      if (memo[newPoint1.first][newPoint1.second] != -1) {
        a = memo[newPoint1.first][newPoint1.second];
      }else {
        a = tryElement2(triangle,newPoint1.first, newPoint1.second);
        memo[newPoint1.first][newPoint1.second] = a;
      }
    }

    if (inTriangle(newPoint2.first, newPoint2.second)) {
      if (memo[newPoint2.first][newPoint2.second] != -1) {
        b = memo[newPoint2.first][newPoint2.second];
      }else {
        b = tryElement2(triangle,newPoint2.first, newPoint2.second);
        memo[newPoint2.first][newPoint2.second] = b;
      }
    }

    return triangle[x][y] + std::min(a, b);
  }

  void printV(vector<int> memo, int len) {
    for (int i = 0; i < len; ++i)
      std::cout << memo[i] << " ";
    std::cout << std::endl;
  }

  /// 动态规划
  int tryElement3(vector<vector<int>>& triangle) {
    int n = triangle.size();
    /// 初始化数组的技巧
    vector<int> memo(triangle.back());

    /// 初始条件，最后一层的值，也即他们所能获得的最小值
//    for (int i = 0; i < n; ++i) {
//      memo[i] = triangle[n-1][i];
//    }

//    printV(memo, n);

    /// 自下往上迭代，自左往右迭代 （迭代的方向就是不能影响下一次迭代）
    for (int i = n-2; i >= 0; --i) {
      for (int j = 0; j <= i; ++j) {
        memo[j] = triangle[i][j] + std::min(memo[j], memo[j + 1]);
      }
//      printV(memo, i+1);
    }

    return memo[0];
  }
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    maxRow = triangle.size();
    if (maxRow == 0)
      return 0;
    return tryElement(triangle, 0, 0);
  }

  int minimumTotal2(vector<vector<int>>& triangle) {
    maxRow = triangle.size();
    if (maxRow == 0)
      return 0;
    memo = vector<vector<int>>(maxRow, vector<int>(maxRow, -1));
    return tryElement2(triangle, 0, 0);
  }

  int minimumTotal3(vector<vector<int>>& triangle) {
    if (triangle.size() == 0)
      return 0;
    return tryElement3(triangle);
  }
};

/**
 *  [
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
 自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）
 */
int main() {

  vector<vector<int>> triangle{
      {2},
      {3,4},
      {6,5,7},
      {4,1,8,3}
  };

  time_t start = clock();
  int minimum = Solution().minimumTotal(triangle);
  time_t end = clock();
  std::cout << "minimum: " << minimum << endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  start = clock();
  minimum = Solution().minimumTotal2(triangle);
  end = clock();
  std::cout << "minimum: " << minimum << endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  start = clock();
  minimum = Solution().minimumTotal3(triangle);
  end = clock();
  std::cout << "minimum: " << minimum << endl;
  std::cout << "time: " << (double)(end - start)/1000 << "ms" << std::endl;

  return 0;
}