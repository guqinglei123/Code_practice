/***************************************************************************************************
问题一：(最长公共子序列)一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余
字符相对位置所组成的新字符串。给定两个序列：X[1...m]和Y[1...n]，求在两个序列中同时出现的最长子序列的长度.
说明：
    给出”ABCD” 和 “EDCA”，这个LCS是 “A” (或 D或C)，返回1 
    给出 “ABCD” 和 “EACB”，这个LCS是”AC”返回 2
参考链接：https://blog.csdn.net/ljyljyok/article/details/77905681

问题二：（最长递增子序列）

参考链接

问题？：(不同的子序列)给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。
说明：
    输入: S = "rabbbit", T = "rabbit"
    输出: 3
    如下图所示, 有 3 种可以从 S 中得到 "rabbit" 的方案。(上箭头符号 ^ 表示选取的字母)
    rabbbit
    ^^^^ ^^
    rabbbit
    ^^ ^^^^
    rabbbit
    ^^^ ^^^

    输入: S = "babgbag", T = "bag"
    输出: 5
    解释:
    如下图所示, 有 5 种可以从 S 中得到 "bag" 的方案。  (上箭头符号 ^ 表示选取的字母)
    babgbag
    ^^ ^
    babgbag
    ^^    ^
    babgbag
    ^    ^^
    babgbag
    ^  ^^
    babgbag
        ^^^
参考链接：https://www.cnblogs.com/felixfang/p/3875141.html
 * ********************************************************************************************/

#include <vector>
#include <list>
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
    int LCS_dp(string s, string t)
    {
        int size1 = s.size();
        int size2 = t.size();
        const char *s1 = s.c_str() - 1; //从1开始数，方便后面的代码编写(将字符串指针str1指向了 首元素的前面。)，这样第0行/列，LCS（即c[0][j],c[i][0]) 为0。
        const char *s2 = t.c_str() - 1;
        vector<vector<int>> chess(size1 + 1, vector<int>(size2 + 1));
        //求解动态规划表,代表含义：m[i, j]表示 s1[i]结尾的子序列 和s2[j]结尾的子序列的最长公共子序列的长度
        //因为是从1起数。而第0行/列是外加的（因为字符串与空串的LCS永远为0）;但是总长需要+1
        //chess棋盘：二维数组，行数为size1，列数为size2
        int i, j;
        for (i = 1; i < size1; i++)
        { // 一定要从1起！！！
            for (j = 1; j < size2; j++)
            {
                if (s1[i] == s2[j])
                {
                    //若两串当前元素相同，则其当前LCS等于左上角LCS（chess[i - 1][j - 1] ）+ 1（此处加的1，即为当前元素(i,j).）
                    chess[i][j] = chess[i - 1][j - 1] + 1;
                }
                else
                { // if (s1[i] != s2[j])
                    //若两串当前元素不同，则其当前LCS一定等于左边、上边的LCS的最大值。（而到了（i,j）处，不是公共元素。跳过。）
                    chess[i][j] = max(chess[i - 1][j], chess[i][j - 1]);
                }
            }
        }
        //到此，排表（棋盘）结束。

        //求解子序列LCS（之一）
        string str;
        i = size1; //将i、j下标落到末尾元素上。
        j = size2;
        while (i != 0 && j != 0)
        {
            if (s1[i] == s2[j])
            { //将相同的子元素压栈。然后指针前移，直到i、j指向0终止(因为任何字符串 与0 求公共子序列，都是0)
                str.push_back(s1[i]);
                i--;
                j--;
            }
            else
            { //若二者不相等，而最长公共子序列一定是由LCS（chess[i][j-1] or chess[i-1][j]）的较大者得来，故将较大者的指针前移，接着遍历。
                if (chess[i][j - 1] > chess[i - 1][j])
                {
                    j--; //将当前列前移到j-1列
                }
                else
                { // if(chess[i][j - 1] <= chess[i - 1][j])
                    i--;
                }
            }
        }
        reverse(str.begin(), str.end());
        cout << "LCS: " << str << endl;
        //求LCS的长度
        int maxLen = 0;
        for (i = 0; i < size1; i++)
        {
            for (j = 0; j < size2; j++)
            {
                maxLen = max(maxLen, chess[i][j]);
            }
        }
        return maxLen;
    }
    //问题二
    //方法一，将排序之后的序列与原序列按问题一的方法求解。
    //方法二，二分查找方法
    int BiSearch(vector<int> &b, int len, int w)
    {
        int left = 0, right = len - 1;
        int mid;
        while (left <= right)
        {
            mid = left + (right - left) / 2;
            if (b[mid] > w)
                right = mid - 1;
            else if (b[mid] < w)
                left = mid + 1;
            else //找到了该元素，则直接返回
                return mid;
        }
        return left; //数组b中不存在该元素，则返回该元素应该插入的位置
    }
    int lengthOfLIS(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        int n = nums.size();
        int len = 1;
        vector<int> B(n, 0);
        B[0] = nums[0];
        int i, pos = 0;

        for (i = 1; i < n; ++i)
        {
            if (nums[i] > B[len - 1]) //如果大于B中最大的元素，则直接插入到B数组末尾
            {
                B[len] = nums[i];
                ++len;
            }
            else
            {
                pos = BiSearch(B, len, nums[i]); //二分查找需要插入的位置
                B[pos] = nums[i];
            }
        }

        return len;
    }
    //方法三，动态规划方法
    int lengthOfLIS_dp(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        int res = 0;
        vector<int> sub(nums.size(), 0);
        for (int i = 1; i < nums.size(); i++)
        {
            sub[i] = 1;
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j] && sub[i] < sub[j] + 1)
                {
                    sub[i] = sub[j] + 1; //计算以nums[i]结尾的序列的最长递增子序列长度
                }
            }
        }
        res = sub[nums.size() - 1];
        return res;
    }
    //问题三
    int numDistinct(string s, string t)
    {
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution Sol;
    //问题一
    string s1;
    string s2;
    s1 = "TCGGATCGACTT";
    s2 = "AGCCTACGTA";
    // s1 = "rabbbit";
    // s2 = "rabbit";
    string str;
    int res = Sol.LCS_dp(s1, s2);
    cout << "LCS length: " << res << endl;

    //问题二
    vector<int> nums;
    nums = {10, 9, 2, 5, 3, 7, 101, 18};
    res = Sol.lengthOfLIS(nums);
    cout << "LIS length:  " << res << endl;
    res = Sol.lengthOfLIS_dp(nums);
    cout << "LIS length of dp:  " << res << endl;

    //问题三
    return 0;
}
