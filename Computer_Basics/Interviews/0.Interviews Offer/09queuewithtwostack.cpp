#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;
class Solution
{
  public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        int stack1_size=stack1.size();
        for (int i = 0; i < stack1_size; i++)
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        int res=stack2.top();
        stack2.pop();
        int stack2_size=stack2.size();
        for (int i = 0; i < stack2_size; i++)
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        return res;
    }
    bool empty()
    {
        if(stack1.empty())
            return true;
        else
            return false;
    }

  private:
    stack<int> stack1;
    stack<int> stack2;
};
int main(int argc, char const *argv[])
{
    /* code */
    Solution solu;
    solu.push(1);
    solu.push(2);
    solu.push(3);
    solu.push(4);
    int node;

    while (solu.empty() != true)
    {

        cout << solu.pop();
    }
    cout<<endl;
    return 0;
}
