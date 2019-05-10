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
    int MoreThanHalfNum_Solution(vector<int> numbers)
    {
        if (numbers.empty())
            return 0;
        int maj;
        //必要性
        for (int c = 0, i = 0; i < numbers.size(); i++)
            if (0 == c)
            {
                maj = numbers[i];
                c = 1;
            }
            else
                maj == numbers[i] ? c++ : c--;

        //充分性
        int occurrence = 0;
        for (int i = 0; i < numbers.size(); i++)
            if (maj == numbers[i])
                occurrence++;
        if (2 * occurrence <= numbers.size())
            return 0;
        return maj;
    }
    int MoreThanHalfNum_Solution2(vector<int> input)
    {
        if (input.empty())
            return 0;
        vector<int> res_vect;
        int k = (input.size() >> 1)+1;
        for (int begin = 0, end = input.size() - 1; begin <= end;)
        {
            int pivot = begin;
            int index = begin + 1;
            for (int i = index; i < end; i++)
            {
                if (input[i] < input[pivot])
                {
                    swap(input, i, index);
                    index++;
                }
            }
            swap(input, pivot, index - 1);
            if (index - 1 > k - 1)
                end = index - 2;
            else
                begin = index;
            if (index == k)
                break;
        }
        //充分性
        int occurrence = 0;
        for (int i = 0; i < input.size(); i++)
            if (input[k - 1] == input[i])
                occurrence++;
        if (2 * occurrence <= input.size())
            return 0;
        return input[k- 1];
    }
    void swap(vector<int> &str, int index1, int index2)
    {
        int temp;
        temp = str[index1];
        str[index1] = str[index2];
        str[index2] = temp;
    }
};

class Test_Solution
{
  public:
    Solution Sol;
    void Test(char *testName, int *numbers, int length, int expectedValue, bool expectedFlag)
    {
        if (testName != nullptr)
            printf("%s begins: \n", testName);
        bool g_bInputInvalid = false;
        vector<int> copy1, copy2;
        for (int i = 0; i < length; ++i)
        {
            copy1.push_back(numbers[i]);
            copy2.push_back(numbers[i]);
        }
        printf("Test for solution1: ");
        int result = Sol.MoreThanHalfNum_Solution(copy1);
        if (result == 0)
            g_bInputInvalid = true;
        if (result == expectedValue && g_bInputInvalid == expectedFlag)
            printf("Passed.\n");
        else
            printf("Failed.\n");

        printf("Test for solution2: ");
        result = Sol.MoreThanHalfNum_Solution2(copy2);
        if (result == 0)
            g_bInputInvalid = true;
        if (result == expectedValue && g_bInputInvalid == expectedFlag)
            printf("Passed.\n");
        else
            printf("Failed.\n");
    }

    // ´æÔÚ³öÏÖ´ÎÊý³¬¹ýÊý×é³¤¶ÈÒ»°ëµÄÊý×Ö
    void Test1()
    {
        int numbers[] = {1, 2, 3, 2, 2, 2, 5, 4, 2};
        Test("Test1", numbers, sizeof(numbers) / sizeof(int), 2, false);
    }

    // ²»´æÔÚ³öÏÖ´ÎÊý³¬¹ýÊý×é³¤¶ÈÒ»°ëµÄÊý×Ö
    void Test2()
    {
        int numbers[] = {1, 2, 3, 2, 4, 2, 5, 2, 3};
        Test("Test2", numbers, sizeof(numbers) / sizeof(int), 0, true);
    }

    // ³öÏÖ´ÎÊý³¬¹ýÊý×é³¤¶ÈÒ»°ëµÄÊý×Ö¶¼³öÏÖÔÚÊý×éµÄÇ°°ë²¿·Ö
    void Test3()
    {
        int numbers[] = {2, 2, 2, 2, 2, 1, 3, 4, 5};
        Test("Test3", numbers, sizeof(numbers) / sizeof(int), 2, false);
    }

    // ³öÏÖ´ÎÊý³¬¹ýÊý×é³¤¶ÈÒ»°ëµÄÊý×Ö¶¼³öÏÖÔÚÊý×éµÄºó°ë²¿·Ö
    void Test4()
    {
        int numbers[] = {1, 3, 4, 5, 2, 2, 2, 2, 2};
        Test("Test4", numbers, sizeof(numbers) / sizeof(int), 2, false);
    }

    // ÊäÈë¿ÕÖ¸Õë
    void Test5()
    {
        int numbers[] = {1};
        Test("Test5", numbers, 1, 1, false);
    }

    // ÊäÈë¿ÕÖ¸Õë
    void Test6()
    {
        Test("Test6", nullptr, 0, 0, true);
    }
};
int main(int argc, char *argv[])
{
    Test_Solution test;
    test.Test1();
    test.Test2();
    test.Test3();
    test.Test4();
    test.Test5();
    test.Test6();

    return 0;
}