//题目

//常用头文件
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cstring>
using namespace std;
class Solution
{
  public:
    int ValidSubbracket(string str)
    {
        int res = 0, num = 0;
        if (str.size() <= 0)
            return 0;

        stack<int> sta;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '(')
                sta.push(i);
            else if (str[i] == ')')
            {
                if (sta.empty())
                    num = i + 1;
                else
                {
                    sta.pop();
                    if(sta.empty())
                        res = max(res, i - num + 1);
                    else
                        res = max(res, i - sta.top());
                }
            }
        }
        return res;   
    }
    int ValidSubbracket2(string str)
    {
        if (str.length() < 2)
        {
            return 0;
        }
        vector<int> vec(str.length(), 0);
        int res = 0;
        for (int i = 1; i < str.length(); i++)
        {
            int num = vec[i - 1];
            if (vec[i - 1] != i - 1)
            {
                num--;
            }
            if (str[num] == '(' && str[i] == ')')
            {
                vec[i] = (num - 1 >= 0 && vec[num - 1] != num - 1) ? vec[num - 1] : vec[num];
            }
            else
            {
                vec[i] = i;
            }
            if (i != vec[i] && res < (i - vec[i] + 1))
            {
                res = (i - vec[i] + 1);
            }
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution Sol;
    string str1, str2;
    while (cin >> str1)
    {
        //对数据的处理主体
        cout << Sol.ValidSubbracket(str1) << endl;//leetcode中全部用例通过，但是测试中没有
        cout << Sol.ValidSubbracket2(str1) << endl;//全部用例通过。
    }
}