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
    int jumpFloorII(int number)
    {
        vector<int> vect(number + 1);
        if (number < 0)
            return 0;
        else if (number < 3)
        {
            vect[number] = number;
        }
        else
        {
            vect[0] = 0;
            vect[1] = 1;
            vect[2] = 2;
        }
        for (int i = 3; i <= number; i++)
        {
            vect[i] = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                vect[i] = vect[i] + vect[j];
            }
            vect[i]=vect[i]+1;//还存在一种直接跳到n阶的情况
        }
        return vect[number];
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution solu;
    cout << solu.jumpFloorII(3) << endl;
    return 0;
}
