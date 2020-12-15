/**********************************
 * File:     main.cpp.c
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2020/12/15
 ***********************************/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        unordered_set<string> visited;

        queue<pair<string, int>> queue;
        queue.push(make_pair(beginWord, 0));
        visited.insert(beginWord);

        while (!queue.empty()) {
            string w = queue.front().first;
            int level = queue.front().second;
            queue.pop();

            if (w == endWord) {
                return level + 1;
            }

            for (int i = 0; i < w.size(); ++i) {
                int t = w[i];
                for (int j = 0; j < 26; j++) {
                    if (w[i] != 'a' + j) {
                        w[i] = 'a' + j;

                        if (dict.count(w)) {
                            if (!visited.count(w)) {
                                queue.push(make_pair(w, level + 1));
                                visited.insert(w);
                            }
                        }

                        w[i] = t;
                    }
                }
            }
        }

        return 0;
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