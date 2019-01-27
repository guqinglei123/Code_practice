#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mylist.h"
using namespace std;
class Solution
{
  public:
    bool match(char *str, char *pattern)
    {

        int index_s = 0;
        int index_p = 0;
        // if((pattern[index_p+1] == '*')&&(pattern[index_p+2] == '\0') && (str[index_s] == '\0'))
        //     return true;
        while ((pattern[index_p] != '\0'))
        {
            if (str[index_s] == '\0')
            {
                if (pattern[index_p] == '*')
                {
                    index_p++;
                }
                else if (pattern[index_p + 1] == '*')
                {
                    index_p++;
                    index_p++;
                }
                else
                    break;
            }
            else if ((pattern[index_p] == str[index_s]) || (pattern[index_p] == '.')) //字符匹配，。理解为与任意字符匹配
            {
                index_p++;
                index_s++;
            }
            else if (pattern[index_p + 1] == '*') //当前字符不相等，但后一位为*，移动两位。
            {
                index_p++;
                index_p++;
            }
            else if (pattern[index_p] == '*') //该字符为*导致不相等.这部分的处理存在问题，没有通过
            {
                if (pattern[index_p - 1] == '.')
                {
                    return true;
                }
                else
                {
                    while (pattern[index_p - 1] == str[index_s]) //前面的字符还有可能时.
                    {
                        if (str[index_s] != '\0')
                            index_s++;
                        else if ((pattern[index_p + 1] == '*'))
                        {
                            index_p++;
                            break;
                        }
                        else if ((pattern[index_p + 2] == '*'))
                        {
                            index_p++;
                            index_p++;
                            break;
                        }
                    }
                    index_p++;
                }
            }
            else
                return false;
        }
        if ((pattern[index_p] == '\0') && (str[index_s] == '\0')) //匹配完成
            return true;
        else if ((pattern[index_p] == '\0') || (str[index_s] == '\0')) //存在一个字符串长度更短
            return false;
    }
};

void Test(const char *testName, char *string, char *pattern, bool expected) //字符串前加const是比较合适的
{
    Solution Sol;
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (Sol.match(string, pattern) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char const *argv[])
{
    /* code */
    Test("Test01", "", "", true);
    Test("Test02", "", ".*", true); //特殊处理
    Test("Test03", "", ".", false);
    Test("Test04", "", "c*", true); //和2一样
    Test("Test05", "a", ".*", true);
    Test("Test06", "a", "a.", false);
    Test("Test07", "a", "", false);
    Test("Test08", "a", ".", true);
    Test("Test09", "a", "ab*", true);
    Test("Test10", "a", "ab*a", false);
    Test("Test11", "aa", "aa", true);
    Test("Test12", "aa", "a*", true);
    Test("Test13", "aa", ".*", true);
    Test("Test14", "aa", ".", false);
    Test("Test15", "ab", ".*", true);
    Test("Test16", "ab", ".*", true);
    Test("Test17", "aaa", "aa*", true);
    Test("Test18", "aaa", "aa.a", false);
    Test("Test19", "aaa", "a.a", true);
    Test("Test20", "aaa", ".a", false);
    Test("Test21", "aaa", "a*a", true);//没有通过
    Test("Test22", "aaa", "ab*a", false);
    Test("Test23", "aaa", "ab*ac*a", true);
    Test("Test24", "aaa", "ab*a*c*a", true);//没有通过
    Test("Test25", "aaa", ".*", true);
    Test("Test26", "aab", "c*a*b", true);
    Test("Test27", "aaca", "ab*a*c*a", true);
    Test("Test28", "aaba", "ab*a*c*a", false);
    Test("Test29", "bbbba", ".*a*a", true);
    Test("Test30", "bcbbabab", ".*a*a", false);//没有通过
    return 0;
}
