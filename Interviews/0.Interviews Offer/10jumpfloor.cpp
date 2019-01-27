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
    int jumpFloor(int number)
    {
        vector<int> vect(number + 1);
        if(number < 0)
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
            vect[i] = vect[i - 1] + vect[i - 2];
        }
        return vect[number];
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution solu;
    cout << solu.jumpFloor(3) << endl;
    return 0;
}
