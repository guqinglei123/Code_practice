// #include <vector>
// #include <list>
// #include <stack>
// #include <algorithm>
#include <iostream>
// #include <stdlib.h>
// #include <cstdlib>
// #include <stdio.h>
// #include <string.h>
// #include <math.h>
using namespace std;
class Solution
{
  public:
    double Power(double base, int exponent)
    {
        double res = 1;
        int nums = exponent;
        if (nums == 0)
            return res;
        if (equal_double(base, 0.0)) //base不能为0的时候没有考虑，而且浮点数的比较不能直接使用等于而要考虑误差
            return 0;
        while (nums != 0)
        {
            if (nums < 0)
            {
                nums++;
                res = res / base;
            }

            else
            {
                nums--;
                res = res * base;
            }
        }
        return res;
    }
    bool equal_double(double num1, double num2)
    {
        if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
            return true;
        else
            return false;
    }
    double Power2(double base, int exponent)
    {
        return 0;
    }

};
int main(int argc, char const *argv[])
{
    /* code */
    Solution solu;
    cout << (double)solu.Power(0, -1) << endl;
    cout << (double)solu.Power2(2.5, -2) << endl;
    return 0;
}