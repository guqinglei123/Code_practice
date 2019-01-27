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
    //递归方法
    //循环（迭代）
    int Fibonacci(int n)
    {
        vector<int>  vect(n+1);
        vect[0]=0;
        vect[1]=1;
        for(int i=2; i <=n; i++)
        {
            vect[i]=vect[i-1]+vect[i-2];
        }
        return vect[n];
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution solu;
    cout << solu.Fibonacci(12) << endl;
    return 0;
}
