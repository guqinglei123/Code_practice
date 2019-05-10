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
using namespace std;
class Solution
{
  public:
    int NumberOf1(int n)
    {
        int res = 0;
        if (n == 0)
            res = 0;
        long unsigned int devide;//注意类型，注意会溢出
        if (n < 0)
        {
            devide = pow(2, 32) + n; //负数不是直接最高取1，按补码。求负整数的补码.
                                     //将其对应正数二进制表示所有位取反（包括符号位，0变1，1变0）后加1
        }
        else
        {
            devide = n;
        }        
        while (devide > 0)
        {
            if ((devide % 2) == 1)//对2取余可以看做&1
                 res++;
            devide = devide / 2;//除以2可以看做<<1

        }
        return res;
    }
        int NumberOf1_2(int n)
    {
        int res;
        while(n)
        {
            ++res;
            n=(n-1)&n;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution solu;
    cout << solu.NumberOf1(-1) << endl;
    cout << solu.NumberOf1_2(-1) << endl;
    return 0;
}
