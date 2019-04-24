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
    vector<int> printMatrix(vector<vector<int>> matrix)
    {

        int rows = matrix.size();
        int columns = matrix[0].size();
        vector<int> res_vec;
        if ((rows == 1) && (columns == 1))
        {
            printf("%d\t", matrix[0][0]);
            res_vec.push_back(matrix[0][0]);
            return res_vec;
        }
        int i = 0, j = 0, nums = 0;

        while ((columns > nums * 2) && (rows > nums * 2))//注意这个终止条件，观察每一圈的终止条件
        {
            // printf("%d\t", matrix[i][j]);

            while (j < (columns - nums))
            {

                printf("%d\t", matrix[i][j]);
                res_vec.push_back(matrix[i][j]);
                j++;
            }
            j--;
            i++;
            if (nums < (rows - nums -1))   //注意这个判断条件，至少还想要一行才可以往下走，即两行一列
            {
                while (i < (rows - nums))
                {

                    printf("%d\t", matrix[i][j]);
                    res_vec.push_back(matrix[i][j]);
                    i++;
                }
                j--;
                i--;
            }

            if ((nums < (rows - nums -1)) && (nums < (columns - nums -1)))//至少还需要一列才可以在左走，即两行两列
            {
                while (j >= nums)
                {

                    printf("%d\t", matrix[i][j]);
                    res_vec.push_back(matrix[i][j]);
                    j--;
                }
                j++;
                i--;
            }

            if ((nums < (rows - nums -2)) && (nums < (columns - nums -1)))//至少还需要一行才可以在上走，即三行两列
            {
                while (i >nums)
                {

                    printf("%d\t", matrix[i][j]);
                    res_vec.push_back(matrix[i][j]);
                    i--;
                }
                j++;
                i++;
            }
            nums++;
        }
        return res_vec;
    }
    vector<int> printMatrix2(vector<vector<int>> matrix)
    {
        vector<int> res_vec;
        for (int i = 0; i < matrix.size(); i++)
        {
            if (i & 0x01) //奇数
            {
                if (matrix[i].empty())
                    continue;
                int j = matrix[i].size() - 1;
                while (j >= 0)
                {
                    printf("%d\t", matrix[i][j]);
                    res_vec.push_back(matrix[i][j]);
                    j--;
                }
            }
            else //偶数
            {
                int j = 0;
                while (j < matrix[i].size())
                {
                    printf("%d\t", matrix[i][j]);
                    res_vec.push_back(matrix[i][j]);
                    j++;
                }
            }
        }
        return res_vec;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    void Test(int columns, int rows)
    {
        printf("Test Begin: %d columns, %d rows.\n", columns, rows);

        if (columns < 1 || rows < 1)
            return;
        // int **numbers = new int *[rows];
        vector<vector<int>> numbers;
        for (int i = 0; i < rows; ++i)
        {
            vector<int> numbers_temp;
            for (int j = 0; j < columns; ++j)
            {
                numbers_temp.push_back(i * columns + j + 1);
                // numbers_temp[j]=i * columns + j + 1;
                // numbers[i][j] = i * columns + j + 1;
            }
            numbers.push_back(numbers_temp);
        }

        Sol.printMatrix(numbers);
        printf("\n");
    }
};
int main(int argc, char *argv[])
{
    Test_Solution test;
    /*
    1    
    */
    test.Test(1, 1);

    /*
    1    2
    3    4
    */
    test.Test(2, 2);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    */
    test.Test(4, 4);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    21   22   23   24   25
    */
    test.Test(5, 5);

    /*
    1
    2
    3
    4
    5
    */
    test.Test(1, 5);

    /*
    1    2
    3    4
    5    6
    7    8
    9    10
    */
    test.Test(2, 5);

    /*
    1    2    3
    4    5    6
    7    8    9
    10   11   12
    13   14   15
    */
    test.Test(3, 5);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    17   18   19   20
    */
    test.Test(4, 5);

    /*
    1    2    3    4    5
    */
    test.Test(5, 1);

    /*
    1    2    3    4    5
    6    7    8    9    10
    */
    test.Test(5, 2);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14    15
    */
    test.Test(5, 3);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    */
    test.Test(5, 4);

    return 0;
}
