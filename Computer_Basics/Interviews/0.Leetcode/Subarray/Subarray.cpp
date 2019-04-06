/***************************************************************************************************
问题一：（数组的度）给定一个非空且只包含非负数的整数数组 nums, 数组的度的定义是指数组里任一元素出现频数的最大值。
你的任务是找到与 nums 拥有相同大小的度的最短连续子数组，返回其长度。
说明：
    输入: [1, 2, 2, 3, 1]
    输出: 2
    解释: 
    输入数组的度是2，因为元素1和2的出现频数最大，均为2.
    连续子数组里面拥有相同度的有如下所示:
    [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
    最短连续子数组[2, 2]的长度为2，所以返回2.
    输入: [1,2,2,3,1,4,2]
    输出: 6
相关链接：https://blog.csdn.net/linhuanmars/article/details/21314059
问题二：(53最大子数组和)给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
说明：
    输入: [-2,1,-3,4,-1,2,1,-5,4],
    输出: 6
    解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
相关链接：https://blog.csdn.net/anlian523/article/details/75244422
        https://blog.csdn.net/linhuanmars/article/details/21314059

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
        int findShortestSubArray(vector<int>& nums) {
        
    }
    int helper(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return nums[left];
        int mid = left + (right - left) / 2;
        int lmax = helper(nums, left, mid - 1);
        int rmax = helper(nums, mid + 1, right);
        int mmax = nums[mid], t = mmax;
        for (int i = mid - 1; i >= left; --i)
        {
            t += nums[i];
            mmax = max(mmax, t);
        }
        t = mmax;
        for (int i = mid + 1; i <= right; ++i)
        {
            t += nums[i];
            mmax = max(mmax, t);
        }
        return max(mmax, max(lmax, rmax));
    }
    int maxSubArray(vector<int> &nums) //分治
    {
        if (nums.empty())
            return 0;
        return helper(nums, 0, (int)nums.size() - 1);
    }

    int maxSubArray_dp(vector<int> &nums)
    {
        if (nums.size() <= 1)
            return nums[0];

        int l = nums[0];
        int g = nums[0];
        for (int i = 1; i < nums.size(); i++) //修改为 条件运算符来表达可以提高运行时间
        {
            l = max(l + nums[i], nums[i]);
            g = max(g, l);
        }
        return g;
    }

    
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution Sol;
    
    //问题二
    vector<int> nums;
    nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res = Sol.maxSubArray(nums);
    cout << "问题的二分解法：" << res << endl;//???
    int res = Sol.maxSubArray_dp(nums);
    cout << "问题的动态规划解法：" << res << endl;
  
    return 0;
}
