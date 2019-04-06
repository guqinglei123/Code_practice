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
#include <functional>
#include <exception>
using namespace std;
class Solution
{
  private:
    vector<int> input;

  public:
    void Insert(int num)
    {
        input.push_back(num);
    }

    double GetMedian()
    {
        // vector<int> input(data);//下面操作会修改input应该重新赋值
        if (input.empty())
            return 0;
        // throw 1;
        int k = ((input.size() >> 1) + 1);  //注意数组中前n+1个最小值,这样第n+1个为前n+1个数组中的最大值
        for (int begin = 0, end = input.size() - 1; begin <= end;)
        {
            int pivot = begin;
            int index = begin + 1;
            for (int i = index; i <= end; i++)
            {
                if (input[i] < input[pivot])
                {
                    swap(input, i, index);
                    index++;
                }
            }
            swap(input, pivot, index - 1);
            if (index - 1 > k - 1)   //注意轴点为index -1;
                end = index - 2;
            else
                begin = index;
            if (index == k)
                break;
        }

        if (input.size() & 0x01 == 1) //
            return input[k - 1];
        else
            return  ((double)input[k - 2] + (double)input[k - 1]) / 2;
        return input[k];
    }
    void swap(vector<int> &str, int index1, int index2)
    {
        int temp;
        temp = str[index1];
        str[index1] = str[index2];
        str[index2] = temp;
    }
};

class Solution_Test
{
  public:
    void Test(char *testName, Solution &numbers, double expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        if (abs(numbers.GetMedian() - expected) < 0.0000001)
            printf("Passed.\n");
        else
            printf("FAILED.\n");
    }
};
int main(int argc, char *argv[])
{
    Solution numbers;
    Solution_Test test;
    // printf("Test1 begins: ");
    // try
    // {
    //     numbers.GetMedian();
    //     printf("FAILED.\n");
    // }
    // catch(const exception&)
    // {
    //     printf("Passed.\n");
    // }

    numbers.Insert(5);
    test.Test("Test2", numbers, 5);

    numbers.Insert(2);
    test.Test("Test3", numbers, 3.5);

    numbers.Insert(3);
    test.Test("Test4", numbers, 3);

    numbers.Insert(4);
    test.Test("Test6", numbers, 3.5);

    numbers.Insert(1);
    test.Test("Test5", numbers, 3);

    numbers.Insert(6);
    test.Test("Test7", numbers, 3.5);

    numbers.Insert(7);
    test.Test("Test8", numbers, 4);

    numbers.Insert(0);
    test.Test("Test9", numbers, 3.5);

    numbers.Insert(8);
    test.Test("Test10", numbers, 4);

    return 0;
}