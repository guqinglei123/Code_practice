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
    int movingCount(int threshold, int rows, int cols)
    {
        if (threshold < 0 || rows <= 0 || cols <= 0)
            return 0;
        vector<bool> visited(rows * cols, 0);
        int sum = recursive_help(threshold, rows, cols, 0, visited);
        cout << sum << endl;
        return sum;
    }
    int recursive_help(int threshold, int rows, int cols, int index, vector<bool> &visited)
    {
        vector<int> vect;

        visited[index] = 1;
        int count = 1;
        if ((index + 1) < (((index / cols) + 1) * cols))
            if ((sumpoint(index + 1, cols) <= threshold) && (visited[index + 1] == 0))
                vect.push_back(index + 1);
        if ((index - 1) >= (((index / cols)) * cols))
            if ((sumpoint(index - 1, cols) <= threshold) && (visited[index - 1] == 0))
                vect.push_back(index - 1);
        if ((index + cols) < rows * cols)
            if ((sumpoint(index + cols, cols) <= threshold) && (visited[index + cols] == 0))
                vect.push_back(index + cols);
        if ((index - cols) >= 0)
            if ((sumpoint(index - cols, cols) <= threshold) && (visited[index - cols] == 0))
                vect.push_back(index - cols);

        int index_v = 0;
        while (index_v < vect.size()) //vect为空的时候为递归基
        {
            if (visited[vect[index_v]] != 1)//注意这里要先判断是否访问过，然后迭代加
                count =count + recursive_help(threshold, rows, cols, vect[index_v], visited);
            index_v++;
        }
        return count;
    }

    int sumpoint(int index, int cols)
    {
        int rows_start = index / cols;
        int cols_start = index - rows_start * cols;
        int sum_debug = gitdigitsum(rows_start) + gitdigitsum(cols_start);
        return (gitdigitsum(rows_start) + gitdigitsum(cols_start));
    }

    int gitdigitsum(int num)
    {
        int sum = 0;
        while (num)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    void test(char *testName, int threshold, int rows, int cols, int expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        if (Sol.movingCount(threshold, rows, cols) == expected)
            printf("Passed.\n");
        else
            printf("FAILED.\n");
    }

    // ·½¸ñ¶àÐÐ¶àÁÐ
    void test1()
    {
        test("Test1", 5, 10, 10, 21);
    }

    // ·½¸ñ¶àÐÐ¶àÁÐ
    void test2()
    {
        test("Test2", 15, 20, 20, 359);
    }

    // ·½¸ñÖ»ÓÐÒ»ÐÐ£¬»úÆ÷ÈËÖ»ÄÜµ½´ï²¿·Ö·½¸ñ
    void test3()
    {
        test("Test3", 10, 1, 100, 29);
    }

    // ·½¸ñÖ»ÓÐÒ»ÐÐ£¬»úÆ÷ÈËÄÜµ½´ïËùÓÐ·½¸ñ
    void test4()
    {
        test("Test4", 10, 1, 10, 10);
    }

    // ·½¸ñÖ»ÓÐÒ»ÁÐ£¬»úÆ÷ÈËÖ»ÄÜµ½´ï²¿·Ö·½¸ñ
    void test5()
    {
        test("Test5", 15, 100, 1, 79);
    }

    // ·½¸ñÖ»ÓÐÒ»ÁÐ£¬»úÆ÷ÈËÄÜµ½´ïËùÓÐ·½¸ñ
    void test6()
    {
        test("Test6", 15, 10, 1, 10);
    }

    // ·½¸ñÖ»ÓÐÒ»ÐÐÒ»ÁÐ
    void test7()
    {
        test("Test7", 15, 1, 1, 1);
    }

    // ·½¸ñÖ»ÓÐÒ»ÐÐÒ»ÁÐ
    void test8()
    {
        test("Test8", 0, 1, 1, 1);
    }

    // »úÆ÷ÈË²»ÄÜ½øÈëÈÎÒâÒ»¸ö·½¸ñ
    void test9()
    {
        test("Test9", -10, 10, 10, 0);
    }
};

int main(int agrc, char *argv[])
{
    Test_Solution test;
    test.test1();
    test.test2();
    test.test3();
    test.test4();
    test.test5();
    test.test6();
    test.test7();
    test.test8();
    test.test9();

    return 0;
}
