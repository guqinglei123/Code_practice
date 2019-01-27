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
#include <cstring>
using namespace std;
class Solution
{
  private:
  public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        if ((pushV.empty()) || (popV.empty()))
            return false;

        int nlength = pushV.size();
        stack<int> assist_stack;
        int pre_point = -1;
        for (int i = 0; i < nlength; i++)
        {
            int current = popV[i];

            if ((!assist_stack.empty()) && (assist_stack.top() == popV[i]))
            {
                assist_stack.pop();
            }
            else
            {
                if ((pre_point == (nlength - 1)) && (!assist_stack.empty()))
                    return false;
                
                for (int j = pre_point + 1; j < nlength; j++)
                {
                    if (pushV[j] == current)
                    {
                        // assist_stack.push(pushV[j]);
                        pre_point = j;
                        break;
                    }
                    else
                        assist_stack.push(pushV[j]);

                    if ((j == (nlength - 1)) && (pushV[j] != current))
                        return false;
                }
            }
        }
        return true;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    void Test(const char *testName, const int *pPush, const int *pPop, int nLength, bool expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);
        vector<int> pPush_vect(nLength, 0), pPop_vect(nLength, 0);
        for (int i = 0; i < nLength; i++)
        {
            pPush_vect[i] = *(pPush + i);
            pPop_vect[i] = *(pPop + i);
        }

        if (Sol.IsPopOrder(pPush_vect, pPop_vect) == expected)
            printf("Passed.\n");
        else
            printf("failed.\n");
    }

    void Test1()
    {
        const int nLength = 5;
        int push[nLength] = {1, 2, 3, 4, 5};
        int pop[nLength] = {4, 5, 3, 2, 1};

        Test("Test1", push, pop, nLength, true);
    }

    void Test2()
    {
        const int nLength = 5;
        int push[nLength] = {1, 2, 3, 4, 5};
        int pop[nLength] = {3, 5, 4, 2, 1};

        Test("Test2", push, pop, nLength, true);
    }

    void Test3()
    {
        const int nLength = 5;
        int push[nLength] = {1, 2, 3, 4, 5};
        int pop[nLength] = {4, 3, 5, 1, 2};

        Test("Test3", push, pop, nLength, false);
    }

    void Test4()
    {
        const int nLength = 5;
        int push[nLength] = {1, 2, 3, 4, 5};
        int pop[nLength] = {3, 5, 4, 1, 2};

        Test("Test4", push, pop, nLength, false);
    }

    // pushºÍpopÐòÁÐÖ»ÓÐÒ»¸öÊý×Ö
    void Test5()
    {
        const int nLength = 1;
        int push[nLength] = {1};
        int pop[nLength] = {2};

        Test("Test5", push, pop, nLength, false);
    }

    void Test6()
    {
        const int nLength = 1;
        int push[nLength] = {1};
        int pop[nLength] = {1};

        Test("Test6", push, pop, nLength, true);
    }

    void Test7()
    {
        Test("Test7", nullptr, nullptr, 0, false);
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