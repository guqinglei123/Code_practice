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
    vector<string> combination(string str)
    {
        vector<string> res_vect;
        if (str.empty())
            return res_vect;
        sort(str.begin(), str.end()); //去除输入中的重复元素
        res_vect.erase(unique(str.begin(), str.end()), str.end());
        help(str, 0, res_vect);
        return res_vect;
    }
    void help(string &str, int index, vector<string> &res_vect)
    {
        for (int j = index; j < str.size(); j++) //需要打印本身所以要从index开始
        {

        }
    }
    void swap(string &str, int index1, int index2)
    {
        char temp;
        temp = str[index1];
        str[index1] = str[index2];
        str[index2] = temp;
    }
};
class Solution_Test
{
  public:
    Solution Sol;
    void Test(char *pStr)
    {
        if (pStr == nullptr)
            printf("Test for nullptr begins:\n");
        else
            printf("Test for %s begins:\n", pStr);

        Sol.combination(pStr);

        printf("\n");
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution_Test test;
    char string1[] = "";
    test.Test(string1);

    char string2[] = "a";
    test.Test(string2);

    char string3[] = "ab";
    test.Test(string3);

    char string4[] = "abc";
    test.Test(string4);

    char string5[] = "aabcef";
    test.Test(string5);
    return 0;
}
