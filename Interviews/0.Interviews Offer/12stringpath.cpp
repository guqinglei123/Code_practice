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
class Solution
{
  public:
    bool hasPath(const char *matrix, int rows, int cols, const char *str)
    {
        vector<int> vect_start;
        vector<bool> visited(rows * cols, 0);
        bool hasPath = false;
        if (str == NULL)
            return false;
        for (int i = 0; i < rows * cols; i++)
        {
            if (matrix[i] == str[0])
                vect_start.push_back(i);
        }
        int index_v = 0;
        int index_s = 1;          //考虑一下str为空
        if (str[index_s] == '\0') //递归基
            if (!vect_start.empty())
            {
                hasPath = true;
                return true;
            }
        while (index_v < vect_start.size())
        {
            // int rows_start = vect_start[index]/cols;
            // int cols_start = vect_start[index]-rows_start*cols;
            if (recursive_help(matrix, rows, cols, str, vect_start[index_v], index_s, visited))
                return true;
            index_v++;
            if (!hasPath)
            {
                visited[vect_start[index_v-1]] = 0;
            }
        }
        return false;
    }
    bool recursive_help(const char *matrix, int rows, int cols, const char *str, int index, int index_s, vector<bool> &visited)
    {
        if(index_s >= rows*cols)
            return false;

        vector<int> vect;
        bool hasPath = false;
        visited[index] = 1;//更新当前状态
        //构造下一步可能性
        if ((index + 1) < (((index / cols) + 1) * cols))
            if ((matrix[index + 1] == str[index_s]) && (visited[index + 1] == 0))
                vect.push_back(index + 1);
        if ((index - 1) >= (((index / cols)) * cols))
            if ((matrix[index - 1] == str[index_s]) && (visited[index - 1] == 0))
                vect.push_back(index - 1);
        if ((index + cols) < rows * cols)
            if ((matrix[index + cols] == str[index_s]) && (visited[index + cols] == 0))
                vect.push_back(index + cols);
        if ((index - cols) >= 0)
            if ((matrix[index - cols] == str[index_s]) && (visited[index - cols] == 0))
                vect.push_back(index - cols);
        //满足寻找条件
        if (str[index_s + 1] == '\0') //递归基
            if (!vect.empty())
            {
                hasPath = true;
                return true;
            }
        //处理每一个可能性
        int index_v = 0;
        while (index_v < vect.size())
        {
            if (recursive_help(matrix, rows, cols, str, vect[index_v], index_s + 1, visited))
                return true;
            index_v++;
            if (!hasPath)
            {
                visited[vect[index_v-1]] = 0;//撤销当前状态
            }
        }
        return false;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    void Test(const char *testName, const char *matrix, int rows, int cols, const char *str, bool expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        if (Sol.hasPath(matrix, rows, cols, str) == expected)
            printf("Passed.\n");
        else
            printf("FAILED.\n");
    }

    //ABTG
    //CFCS
    //JDEH

    //BFCE
    void Test1()
    {
        const char *matrix = "ABTGCFCSJDEH";
        const char *str = "BFCE";

        Test("Test1", (const char *)matrix, 3, 4, str, true);
    }

    //ABCE
    //SFCS
    //ADEE

    //SEE
    void Test2()
    {
        const char *matrix = "ABCESFCSADEE";
        const char *str = "SEE";

        Test("Test2", (const char *)matrix, 3, 4, str, true);
    }

    //ABTG
    //CFCS
    //JDEH

    //ABFB
    void Test3()
    {
        const char *matrix = "ABTGCFCSJDEH";
        const char *str = "ABFB";

        Test("Test3", (const char *)matrix, 3, 4, str, false);
    }

    //ABCEHJIG
    //SFCSLOPQ
    //ADEEMNOE
    //ADIDEJFM
    //VCEIFGGS

    //SLHECCEIDEJFGGFIE
    void Test4()
    {
        const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
        const char *str = "SLHECCEIDEJFGGFIE";

        Test("Test4", (const char *)matrix, 5, 8, str, true);
    }

    //ABCEHJIG
    //SFCSLOPQ
    //ADEEMNOE
    //ADIDEJFM
    //VCEIFGGS

    //SGGFIECVAASABCEHJIGQEM
    void Test5()
    {
        const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
        const char *str = "SGGFIECVAASABCEHJIGQEM";

        Test("Test5", (const char *)matrix, 5, 8, str, true);
    }

    //ABCEHJIG
    //SFCSLOPQ
    //ADEEMNOE
    //ADIDEJFM
    //VCEIFGGS

    //SGGFIECVAASABCEEJIGOEM
    void Test6()
    {
        const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
        const char *str = "SGGFIECVAASABCEEJIGOEM";

        Test("Test6", (const char *)matrix, 5, 8, str, false);
    }

    //ABCEHJIG
    //SFCSLOPQ
    //ADEEMNOE
    //ADIDEJFM
    //VCEIFGGS

    //SGGFIECVAASABCEHJIGQEMS
    void Test7()
    {
        const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
        const char *str = "SGGFIECVAASABCEHJIGQEMS";

        Test("Test7", (const char *)matrix, 5, 8, str, false);
    }

    //AAAA
    //AAAA
    //AAAA

    //AAAAAAAAAAAA
    void Test8()
    {
        const char *matrix = "AAAAAAAAAAAA";
        const char *str = "AAAAAAAAAAAA";

        Test("Test8", (const char *)matrix, 3, 4, str, true);
    }

    //AAAA
    //AAAA
    //AAAA

    //AAAAAAAAAAAAA
    void Test9()
    {
        const char *matrix = "AAAAAAAAAAAA";
        const char *str = "AAAAAAAAAAAAA";

        Test("Test9", (const char *)matrix, 3, 4, str, false);
    }

    //A

    //A
    void Test10()
    {
        const char *matrix = "A";
        const char *str = "A";

        Test("Test10", (const char *)matrix, 1, 1, str, true);
    }

    //A

    //B
    void Test11()
    {
        const char *matrix = "A";
        const char *str = "B";

        Test("Test11", (const char *)matrix, 1, 1, str, false);
    }

    void Test12()
    {
        Test("Test12", nullptr, 0, 0, nullptr, false);
    }
};
int main(int argc, char *argv[])
{
    Test_Solution test;
    test.Test1();
    test.Test2();
    test.Test3();
    test.Test4();
    test.Test5();
    test.Test6();
    test.Test7();
    test.Test8();
    test.Test9();
    test.Test10();
    test.Test11();
    test.Test12();

    return 0;
}