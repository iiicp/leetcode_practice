/**********************************
 * File:     main2.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/16
 ***********************************/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;
class Solution {
  class point {
  public:
    int x;
    int y;
    int level;

    point(int x, int y, int level): x(x), y(y), level(level) {};
  };
public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    int end = find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
    if (end == wordList.size())
      return 0;

    int begin = find(wordList.begin(), wordList.end(), beginWord) - wordList.begin();
    if (begin == wordList.size())
      wordList.push_back(beginWord);

    int n = wordList.size();

    std::cout << "begin: " << begin << ", " << begin << std::endl;
    std::cout << "end: " << end << ", " << end << std::endl;

    vector<vector<bool>> g(n, vector<bool>(n, false));
    for (int i = 0; i < wordList.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        g[i][j] = g[j][i] = similar(wordList[i], wordList[j]);
      }
    }

    vector<vector<bool>> visited(n, vector<bool>(n, false));

    // bfs
    queue<point> q;
    q.push(point(begin, begin, 1));

    visited[begin][begin] = true;

    while (!q.empty()) {
      point p = q.front();
      q.pop();
      if (p.x == end && p.y == end) {
        return p.level;
      }
//      for (int i = 0; i < 4; ++i) {
        if (p.x - 1 >= 0 && g[p.x-1][p.y] && !visited[p.x-1][p.y]) {
          q.push(point(p.x - 1, p.y, p.level + 1));
          visited[p.x-1][p.y] = true;
        }

        if (p.x + 1 < n && g[p.x+1][p.y] && !visited[p.x+1][p.y]) {
          q.push(point(p.x + 1, p.y, p.level + 1));
          visited[p.x+1][p.y] = true;
        }

        if (p.y - 1 >= 0 && g[p.x][p.y-1] && !visited[p.x][p.y-1]) {
          q.push(point(p.x, p.y - 1, p.level + 1));
          visited[p.x][p.y-1] = true;
        }

        if (p.y + 1 < n && g[p.x][p.y+1] && !visited[p.x][p.y+1]) {
          q.push(point(p.x, p.y + 1, p.level + 1));
          visited[p.x][p.y+1] = true;
        }
//      }
    }
    return 0;
  }

  bool similar(const string &word1, const string &word2) {
    assert(word1 != "" && word1.size() == word2.size() && word1 != word2);
    int diff = 0;
    for (int i = 0; i < word1.size(); ++i) {
      if (word1[i] != word2[i]) {
        diff++;
        if (diff > 1)
          return false;
      }
    }
    return true;
  }
};

int main()
{
  string beginWord = "hit";
  string endWord = "cog";
  vector<string> wordList = {"hot","dot","dog","lot","log", "cog"};

  int len = Solution().ladderLength(beginWord, endWord, wordList);
  std::cout << len << std::endl;
  return 0;
}