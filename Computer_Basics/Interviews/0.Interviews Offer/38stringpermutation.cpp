#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cstring>
using namespace std;
class Solution
{
  public:
    vector<string> Permutation(string str)
    {
        vector<string> res_vect;
        if (str.empty())
            return res_vect;
        help(str, 0, res_vect);
        sort(res_vect.begin(), res_vect.end()); //以防重复元素，也可以使用set来解决这个问题
        res_vect.erase(unique(res_vect.begin(), res_vect.end()), res_vect.end());
        for (auto it = res_vect.begin(); it != res_vect.end(); it++)
            cout << (*it) << ' ';
        return res_vect;
    }
    void help(string &str, int index, vector<string> &res_vect)
    {

        if (index == str.size()) //注意打印条件
        {
            res_vect.push_back(str);
        }
        else
        {
            for (int j = index; j < str.size(); j++) //需要打印本身所以要从index开始
            {
                swap(str, index, j);
                help(str, index + 1, res_vect);
                swap(str, index, j); //注意要变换回来
            }
        }
    }
    void swap(string &str, int index1, int index2)
    {
        char temp;

        temp = str[index1];
        str[index1] = str[index2];
        str[index2] = temp;
    }
    //递归
    vector<string> Permutation_recursion(string str)
    {
        vector<string> res_vect;
        if (str.empty())
            return res_vect;
        sort(str.begin(), str.end());
        do
        {
            res_vect.push_back(str);
        } while (next_permutation(str));
        //去除重复元素
        sort(res_vect.begin(), res_vect.end()); //以防重复元素，也可以使用set来解决这个问题
        res_vect.erase(unique(res_vect.begin(), res_vect.end()), res_vect.end());
        for (auto it = res_vect.begin(); it != res_vect.end(); it++)
            cout << (*it) << ' ';
        return res_vect;
    }

    bool next_permutation(string &str) //下一个全排列
    {

        int i, k;//k为最后（最右）一个升序的首位位置
                         //i为第p位右边最后一个比str[k]大的位置
                          
        // 从右向左寻找非递减序列,例如对于序列1,3,5,4,2,将会找到数字5的位置
        for (k = str.size() - 1; k > 0 && str[k - 1] >= str[k]; k--)
            ;
        if (k == 0)
            return false;
        //从非递减序列李寻找比它前面的一个数(3)大的最小数,即数字4
        for (i = str.size() - 1; str[i] <= str[k - 1]; i--)
            ;
        swap(str, k-1, i);
        //把第(k+ 1)位到最后的部分翻转
        Reverse(str, k, str.size() - 1);
        return true;
    }
    void Reverse(string &str, int begin, int end)
    {
        while (begin < end)
            swap(str, begin++, end--);
    }
};
class Solution_Test
{
  public:
    Solution Sol;
    void Test(char *pStr)
    {
        if (pStr == nullptr)
            printf("Test for nullptr begins:\n");
        else
            printf("Test for %s begins:\n", pStr);

        Sol.Permutation(pStr);
        cout << endl;
        Sol.Permutation_recursion(pStr);

        printf("\n");
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution_Test test;
    char string1[] = "";
    test.Test(string1);

    char string2[] = "a";
    test.Test(string2);

    char string3[] = "ab";
    test.Test(string3);

    char string4[] = "abc";
    test.Test(string4);
    char string5[] = "aabc";
    test.Test(string5);
    return 0;
}
