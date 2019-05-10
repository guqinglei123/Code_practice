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
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {
        vector<int> res_vect;
        if(input.size() < k)//边界条件
            return res_vect;
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

        for (int i = 0; i < k; i++)
            res_vect.push_back(input[i]);
        return res_vect;
    }
    void swap(vector<int> &str, int index1, int index2)
    {
        int temp;
        temp = str[index1];
        str[index1] = str[index2];
        str[index2] = temp;
    }
    vector<int> GetLeastNumbers_Solution2(vector<int> input, int k)
    {
    }
};

class Test_Solution
{
  public:
    Solution Sol;
    void Test(char *testName, int *data, int n, int *expectedResult, int k)
    {
        if (testName != nullptr)
            printf("%s begins: \n", testName);

        vector<int> vectorData1, vectorData2;
        for (int i = 0; i < n; ++i)
        {
            vectorData1.push_back(data[i]);
            vectorData2.push_back(data[i]);
        }  

        if (expectedResult == nullptr)
            printf("The input is invalid, we don't expect any result.\n");
        else
        {
            printf("Expected result: \n");
            for (int i = 0; i < k; ++i)
                printf("%d\t", expectedResult[i]);
            printf("\n");
        }

        printf("Result for solution1:\n");
        vector<int> res_vect;
        res_vect = Sol.GetLeastNumbers_Solution(vectorData1, k);
        sort(res_vect.begin(),res_vect.end());
        if (expectedResult != nullptr)
        {
            for (int i = 0; i < k; ++i)
                printf("%d\t", res_vect[i]);
            printf("\n");
        }

        // printf("Result for solution2:\n");
        // res_vect = Sol.GetLeastNumbers_Solution2(vectorData2, k);
        // printf("The actual output numbers are:\n");
        // if (expectedResult != nullptr)
        // {
        //     for (int i = 0; i < k; ++i)
        //         printf("%d\t", res_vect[i]);
        //     printf("\n");
        // }
    }

    // kÐ¡ÓÚÊý×éµÄ³¤¶È
    void Test1()
    {
        int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
        int expected[] = {1, 2, 3, 4};
        Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
    }

    // kµÈÓÚÊý×éµÄ³¤¶È
    void Test2()
    {
        int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
        Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
    }

    // k´óÓÚÊý×éµÄ³¤¶È
    void Test3()
    {
        int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
        int *expected = nullptr;
        Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
    }

    // kµÈÓÚ1
    void Test4()
    {
        int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
        int expected[] = {1};
        Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
    }

    // kµÈÓÚ0
    void Test5()
    {
        int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
        int *expected = nullptr;
        Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
    }

    // Êý×éÖÐÓÐÏàÍ¬µÄÊý×Ö
    void Test6()
    {
        int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
        int expected[] = {1, 2};
        Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
    }

    // ÊäÈë¿ÕÖ¸Õë
    void Test7()
    {
        int *expected = nullptr;
        Test("Test7", nullptr, 0, expected, 0);
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
    test.Test7();

    return 0;
}