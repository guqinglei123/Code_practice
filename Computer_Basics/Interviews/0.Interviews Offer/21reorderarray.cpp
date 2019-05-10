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
    void reOrderArray(vector<int> &array)
    {

        if (array.empty())
            return;
        if (array.size() == 1)
            return;
        int begins_index = 0;
        int end_index = array.size() - 1;
        while (end_index > begins_index)
        {
            if (((array[begins_index] & 0x01) != 0) && ((array[end_index] & 0x01) == 0)) //前奇数。后为偶数
            {
                begins_index++;
                end_index--;
            }
            else if (((array[begins_index] & 0x01) != 0) && ((array[end_index] & 0x01) != 0)) //前奇数。后为奇数
                begins_index++;
            else if (((array[begins_index] & 0x01) == 0) && ((array[end_index] & 0x01) == 0)) //前偶数。后为偶数
                end_index--;
            else if (((array[begins_index] & 0x01) == 0) && ((array[end_index] & 0x01) != 0)) //前偶数。后为奇数
            {
                swap(array[begins_index], array[end_index]);
                begins_index++;
                end_index--;
            }
        }
    }
    void swap(int &num1, int &num2) //注意这个是引用
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    void reOrderArray2(vector<int> &array) //可以扩展为通用接口
    {
    }
    void reOrderArray3(vector<int> &array) //保持奇数和奇数，偶数和偶数之间的相对位置不变。
    {
        if (array.empty())
            return;
        if (array.size() == 1)
            return;
        int begins_index = 0;
        int end_index = array.size() - 1;
        int odd_nums = 0;
        //1.先统计一下有多少个奇数和偶数
        for (int i = 0; i < array.size() - 1; i++)
            if ((array[begins_index] & 0x01) != 0) //奇数
                odd_nums++;
        //2.在进行交换
        while ((end_index < array.size()) && (begins_index < odd_nums))
        {

        }
    }
};

void PrintArray(vector<int> numbers, int length)
{
    if (length < 0)
        return;

    for (int i = 0; i < length; ++i)
        printf("%d\t", numbers[i]);

    printf("\n");
}

void Test(char *testName, vector<int> numbers, int length)
{
    if (testName != nullptr)
        printf("%s begins:\n", testName);
    vector<int> copy3(numbers);

    Solution Sol;
    printf("Test for solution 1:\n");
    PrintArray(numbers, length);
    Sol.reOrderArray(numbers);
    PrintArray(numbers, length);

    printf("Test for solution 2:\n");
    PrintArray(copy3, length);
    Sol.reOrderArray3(copy3);
    PrintArray(copy3, length);
}

void Test1()
{
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7};
    Test("Test1", numbers, numbers.size());
}

void Test2()
{
    vector<int> numbers = {2, 4, 6, 1, 3, 5, 7};
    Test("Test2", numbers, numbers.size());
}

void Test3()
{
    vector<int> numbers = {1, 3, 5, 7, 2, 4, 6};
    Test("Test3", numbers, numbers.size());
}

void Test4()
{
    vector<int> numbers = {1};
    Test("Test4", numbers, numbers.size());
}

void Test5()
{
    vector<int> numbers = {2};
    Test("Test5", numbers, numbers.size());
}

void Test6()
{
    vector<int> numbers;
    Test("Test6", numbers, 0);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}
