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
    void print1tomaxofNdigits(int n) //直接定义类型，会有长度范围限制
    {
        if (n <= 0)
            return;
        char *number = new char[n + 1];
        memset(number, '0', n); //把每一个数字都初始化为0
        number[n] = '\0';

        while (!increment(number))
        {
            PrintNumber(number);
        }
        delete[] number;
    }
    bool increment(char *number)
    {
        bool isoverflow = false;
        int ntakeover = 0;
        int nlength = strlen(number);
        for (int i = nlength - 1; i >= 0; i--)
        {
            int nsum = number[i] - '0' + ntakeover;
            if (i == nlength - 1)
                nsum++;
            if (nsum >= 10)
            {
                if (i == 0)
                    isoverflow = true;
                else
                {
                    nsum -= 10;
                    ntakeover = 1;
                    number[i] = '0' + nsum;
                }
            }
            else
            {
                number[i] = '0' + nsum;
                break;
            }
        }

        return isoverflow;
    }
    void PrintNumber(char *number)
    {
        bool isbeginning0 = true;
        int nlength = strlen(number);

        for (int i = 0; i < nlength; ++i)
        {
            if (isbeginning0 && number[i] != '0')
                isbeginning0 = false;
            if (!isbeginning0)
            {
                printf("%c", number[i]);
            }
        }
        printf("\t");
    }
    void print1tomaxofNdigits2(int n) //使用递归的方式
    {
        if (n <= 0)
            return;
        char *number = new char[n + 1];
        memset(number, '0', n); //把每一个数字都初始化为0
        number[n] = '\0';
        for(int i = 0; i < 10; ++i)
        {
            number[0] = i + '0';
            recursive_help(number, n,0);
        }
        delete[] number;
    }
    void recursive_help(char * number, int length, int index)
    {
        if(index == length -1)
        {
            PrintNumber(number);
            return;
        }
        for(int i=0; i <10; ++i)
        {
            number[index+1]= i+'0';
            recursive_help(number,length,index+1);
        }
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution Sol;

    Sol.print1tomaxofNdigits(2);
    // Sol.print1tomaxofNdigits2(4);
    return 0;
}
