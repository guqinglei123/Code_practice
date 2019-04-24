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
template <typename T>
class Solution
{
  private:
    stack<T> data_stack;
    stack<T> assist_stack;

  public:
    void push(const T &value)
    {
        data_stack.push(value);
        int min_data = 0;
        if (assist_stack.size() > 0)//注意assist_stack为空的情况
            min_data = assist_stack.top();

        if ((value >= min_data)&&(assist_stack.size() > 0))
            assist_stack.push(min_data);
        else
            assist_stack.push(value);
    }
    void pop()
    {
        data_stack.pop();
        assist_stack.pop();
    }
    T &top()
    {
        return data_stack.top();
    }
    T &min()
    {
        return assist_stack.top();
    }
};
class Test_Solution
{
  public:
    void Test(const char *testName, Solution<int> &stack, int expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        if (stack.min() == expected)
            printf("Passed.\n");
        else
            printf("Failed.\n");
    }
};
int main(int argc, char *argv[])
{
    Solution<int> stack;
    Test_Solution test;

    stack.push(3);
    test.Test("Test1", stack, 3);

    stack.push(4);
    test.Test("Test2", stack, 3);

    stack.push(2);
    test.Test("Test3", stack, 2);

    stack.push(3);
    test.Test("Test4", stack, 2);

    stack.pop();
    test.Test("Test5", stack, 2);

    stack.pop();
    test.Test("Test6", stack, 3);

    stack.pop();
    test.Test("Test7", stack, 3);

    stack.push(0);
    test.Test("Test8", stack, 0);

    return 0;
}