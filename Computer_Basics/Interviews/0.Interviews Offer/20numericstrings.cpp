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
    bool isNumeric(char *string)
    {
        int index = 0;
        if ((string == nullptr) || (string[index] == '\0'))
            return false;
        int pre_index = 0;
        int dot_flag = 0;
        int e_flag = 0;
        while (string[index] != '\0')
        {
            if (string[index] == '.')
            {
                dot_flag++;
                if (dot_flag > 1)
                    return false;
                if (e_flag >= 1)
                    return false;
                if (index != 0)
                {
                    if (!isInteger(1, string, pre_index, index - 1)) //A部分
                        return false;
                    pre_index = index + 1;
                }
            }
            else if ((string[index] == 'e' || string[index] == 'E'))
            {
                e_flag++;
                if (e_flag > 1)
                    return false;
                if (dot_flag == 0)
                {
                    if (!isInteger(1, string, pre_index, index - 1)) //A部分
                        return false;
                }
                else if (dot_flag == 1)
                {
                    if (!isInteger(0, string, pre_index, index - 1)) //B部分
                        return false;
                }
                else
                    return false;
                pre_index = index + 1;
            }
            index++;
            if ((string[index] == '\0'))
                if ((pre_index != index))
                {
                    if (!isInteger(1, string, pre_index, index - 1)) //A或者为C部分
                        return false;
                }
                else//最后一位为非数字
                {
                    if((string[index-1] == '.')&&(isdigit(string[index-2]))) //case 6
                        return true;
                    else
                        return false;
                }
        }
        return true;
    }
    bool isInteger(int sign_flag, char *string, int begins, int end)
    {
        if ((string[begins] == '\0') || (end < begins))
            return false;
        if ((string[begins] == '+') || (string[begins] == '-'))
            if (sign_flag == 0) //不能存在符号
                return false;
            else
                begins++;
        for (int i = begins; i <= end; i++)
            if (!isdigit(string[i]))
                return false;
        return true;
    }
};

void Test(const char *testName, char *str, bool expected)
{
    Solution Sol;
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (Sol.isNumeric(str) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char *argv[])
{
    Test("Test1", "100", true);
    Test("Test2", "123.45e+6", true);
    Test("Test3", "+500", true);
    Test("Test4", "5e2", true);
    Test("Test5", "3.1416", true);
    Test("Test6", "600.", true);
    Test("Test7", "-.123", true);
    Test("Test8", "-1E-16", true);
    Test("Test9", "1.79769313486232E+308", true);

    printf("\n\n");

    Test("Test10", "12e", false);
    Test("Test11", "1a3.14", false);
    Test("Test12", "1+23", false);
    Test("Test13", "1.2.3", false);
    Test("Test14", "+-5", false);
    Test("Test15", "12e+5.4", false);
    Test("Test16", ".", false);
    Test("Test17", ".e1", false);
    Test("Test18", "e1", false);
    Test("Test19", "+.", false);
    Test("Test20", "", false);
    Test("Test21", nullptr, false);

    return 0;
}