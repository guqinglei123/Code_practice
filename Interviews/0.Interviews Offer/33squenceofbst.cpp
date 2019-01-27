#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
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
    bool VerifySquenceOfBST(vector<int> sequence)
    {
        if (sequence.empty())
            return false;
        return help(sequence, 0, sequence.size() - 1);
    }
    bool help(vector<int> &sequence, int begin, int end)
    {
        int mid = begin;
        if(end <= begin)
            return true;
        for (int i = begin; i <= end; i++) //注意这里取等号的情况
        {
            if (sequence[i] >= sequence[end])
            {
                mid = i;
                break;
            }
            // if ((i == (end - 1)) && (sequence[i] < sequence[end]))//找不到的情况
            //     return false;
        }
        for (int j = mid; j < (end - 1); j++)
        {
            if (sequence[j] < sequence[end])
                return false;
        }
        return ((help(sequence, begin, mid - 1)) && (help(sequence, mid, end - 1)));
        // int left = true;
        // int right = true;
        // if (mid > begin) 
        //     left = help(sequence, begin, mid - 1);
        // if (mid < end )
        //     right = help(sequence, mid, end - 1);
        // return (left && right); //分别为左子树与右子树
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    void Test(const char *testName, int sequence[], int length, bool expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        vector<int> sequence_vect;
        for(int i = 0; i< length; i++)
            sequence_vect.push_back(sequence[i]);

        if (Sol.VerifySquenceOfBST(sequence_vect) == expected)
            printf("passed.\n");
        else
            printf("failed.\n");
    }

    //            10
    //         /      \
    //        6        14
    //       /\        /\
    //      4  8     12  16
    void Test1()
    {
        int data[] = {4, 8, 6, 12, 16, 14, 10};
        Test("Test1", data, sizeof(data) / sizeof(int), true);
    }

    //           5
    //          / \
    //         4   7
    //            /
    //           6
    void Test2()
    {
        int data[] = {4, 6, 7, 5};
        Test("Test2", data, sizeof(data) / sizeof(int), true);
    }

    //               5
    //              /
    //             4
    //            /
    //           3
    //          /
    //         2
    //        /
    //       1
    void Test3()
    {
        int data[] = {1, 2, 3, 4, 5};
        Test("Test3", data, sizeof(data) / sizeof(int), true);
    }

    // 1
    //  \
//   2
    //    \
//     3
    //      \
//       4
    //        \
//         5
    void Test4()
    {
        int data[] = {5, 4, 3, 2, 1};
        Test("Test4", data, sizeof(data) / sizeof(int), true);
    }

    // Ê÷ÖÐÖ»ÓÐ1¸ö½áµã
    void Test5()
    {
        int data[] = {5};
        Test("Test5", data, sizeof(data) / sizeof(int), true);
    }

    void Test6()
    {
        int data[] = {7, 4, 6, 5};
        Test("Test6", data, sizeof(data) / sizeof(int), false);
    }

    void Test7()
    {
        int data[] = {4, 6, 12, 8, 16, 14, 10};
        Test("Test7", data, sizeof(data) / sizeof(int), false);
    }

    void Test8()
    {
        Test("Test8", nullptr, 0, false);
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
    test.Test8();

    return 0;
}