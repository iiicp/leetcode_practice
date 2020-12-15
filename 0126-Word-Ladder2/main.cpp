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
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {


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