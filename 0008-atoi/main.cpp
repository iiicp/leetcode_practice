/***********************************
* File:     main.cpp.c
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2020/12/22
***********************************/

#include <string>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        if (str.empty()) {
            return 0;
        }

        int sign = 1;
        long res = 0;


        int size = str.size();
        int i = 0;
        while (str[i] == ' ') {
            i++;
        }

        if (str[i] == '-') {
            sign = -1;
            i++;
        } else if (str[i] == '+'){
            sign = 1;
            i++;
        }

        while (isdigit(str[i])) {
            if (res >= LONG_MAX/10) {
                break;
            }
            long t = str[i] - '0';
            res = res * 10 + t;
            i++;
        }

        res = res * sign;
        if (res < INT_MIN) {
            return INT_MIN;
        }else if (res > INT_MAX) {
            return INT_MAX;
        }else {
            return res ;
        }
    }
};

int main() {

    int res = Solution().myAtoi("+1");
    std::cout << res << std::endl;

    return 0;
}