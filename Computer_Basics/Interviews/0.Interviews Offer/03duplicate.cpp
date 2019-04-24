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
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false

    bool duplicate(int numbers[], int length, int *duplication)
    {
        
        for(int i = 0;i< length-1;i++)
        {
            if(numbers[i] !=i)      //在例子中该处为while。如果只是if判断是否合理。
            {
                if(numbers[numbers[i]]==numbers[i]) //如果没有重复则排序之后i = number[i]. 
                {
                    // cout << numbers[i] << endl;
                    // cout << &numbers[i] << endl; 
                    // duplication = &numbers[i];
                    // cout << duplication <<endl;
                    * duplication = numbers[i];
                    return true;
                }
                else
                {
                    int temp = numbers[i];
                    numbers[i] = numbers[temp];
                    numbers[temp] = temp;

                }
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    int number[] = {2, 3, 1, 0, 2, 5, 3};
    // int number[] = {4, 3, 1, 0, 2, 5, 6};
    int dup;
    Solution Sol;
    Sol.duplicate(number, 7, &dup);
    cout << dup <<endl;
    return 0;
}
