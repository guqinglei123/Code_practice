/***************************************************************************************************
 * 问题一：(1.两数之和)给定一个整数数组和一个目标值，找出数组中和为目标值的两个数。
你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。
说明：
    给定 nums = [2, 7, 11, 15], target = 9
    因为 nums[0] + nums[1] = 2 + 7 = 9
    所以返回 [0, 1]
参考链接：

问题二：（15. 三数之和）给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。
说明：
    例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
    满足要求的三元组集合为：
    [
    [-1, 0, 1],
    [-1, -1, 2]
    ]
参考链接：

问题三：（16. 最接近的三数之和）给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，
使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
说明：
    例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.
    与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).  
参考链接：

问题四：（18. 四数之和）给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，
b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
说明：
    给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
    满足要求的四元组集合为：
    [
    [-1,  0, 0, 1],
    [-2, -1, 1, 2],
    [-2,  0, 0, 2]
    ]
参考链接：
 * ********************************************************************************************/
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
#include <malloc.h>
using namespace std;
class Solution
{
  public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> res_vect;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
                break;                           //大于0的数据之后，不可能三者之和大于0(都是正数)
            if (i > 0 && nums[i] == nums[i - 1]) //注意这里需要i >0，否则[0 0 0]这种情况无法通过测试
                continue;                        //减少重复
            int *pre = &nums[i + 1];
            int *end = &nums[nums.size() - 1];
            int target = 0 - nums[i];
            int twosum = 0;
            while (end > pre)
            {
                twosum = (*pre) + (*end);
                if (twosum == target)
                {
                    res_vect.push_back({nums[i], (*pre), (*end)});
                    while (end > pre && (*pre) == (*(pre + 1)))
                        pre++; //减少重复，注意这时候也要end > pre 保证
                    while (end > pre && (*end) == (*(end - 1)))
                        --end;
                    ++pre;
                    --end;
                }
                else if (twosum < target)
                    ++pre; //增大pre是增大了twosum
                else
                    --end; //减小end是减小了twosum
            }
        }
        return res_vect;
    }
    int threeSumClosest(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int diff2_min = abs(target - nums[0] - nums[1] - nums[nums.size() - 1]);
        int diff2, res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int *pre = &nums[i + 1];
            int *end = &nums[nums.size() - 1];
            while (end > pre)
            {
                diff2 = target - nums[i] - (*pre) - (*end);
                if (diff2_min >= abs(diff2))
                {
                    diff2_min = abs(diff2);
                    res = target - diff2;
                }
                if (diff2 > 0)
                    ++pre; //target大于三者之和，增大pre，增大大于三者之和，减小误差
                else
                    --end; //target小于三者之和，增大end，降低大于三者之和，减小误差
            }
        }
        return res;
    }
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
    }
};

int *twoSum(int *nums, int numsSize, int target)
{
    int num;
    int sum;
    int *address = (int *)malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize; ++i)
    {
        for (int j = i + 1; j < numsSize; ++j)
        {

            sum = nums[i] + nums[j];
            if (sum == target)
            {
                address[0] = i;
                address[1] = j;
            }
        }
    }
    return address;
}
int *twoSum_hash(int *nums, int numsSize, int target)
{
    return NULL;
}

int main(int argc, char const *argv[])
{
    /* code */
    //问题一
    int nums[4] = {11, 7, 2, 15};
    int target = 9;
    int *res_nums;
    res_nums = twoSum(nums, 4, target);      //暴力求解
    res_nums = twoSum_hash(nums, 4, target); //通过hash表求解
    //问题二
    Solution Sol;
    vector<int> nums_vect;
    // nums_vect = {-1, 0, 1, 2, -1, -4};
    nums_vect = {0, 0, 0};
    vector<vector<int>> result_vect;
    result_vect = Sol.threeSum(nums_vect);
    //问题三
    // nums_vect = {-1, 2, 1, -4};
    nums_vect = {0, 0, 0};
    cout << Sol.threeSumClosest(nums_vect, 1) << endl;
    return 0;
}
