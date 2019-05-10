/***************************************************************************************************
 * 问题一：(55跳跃游戏一)给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个位置。
说明：
    输入: [2,3,1,1,4]
    输出: true
    解释: 从位置 0 到 1 跳 1 步, 然后跳 3 步到达最后一个位置。
    输入: [3,2,1,0,4]
    输出: false
    解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。
参考链接：http://www.cnblogs.com/grandyang/p/4371526.html

问题二：(45跳跃游戏二)给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。
说明：
    输入: [2,3,1,1,4]
    输出: 2
    解释: 跳到最后一个位置的最小跳跃数是 2。
        从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
    假设你总是可以到达数组的最后一个位置。
参考链接:http://www.cnblogs.com/grandyang/p/4373533.html

 * ********************************************************************************************/
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
using namespace std;


class Solution {
public:
    bool canJump(vector<int>& nums) 
    {
        if(nums.size() <1 )
            return false;
        int index_k = 0;
        int pre_jump = 0;
        int temp_jump =0;
        int max_i=1;
        int jump=0;
        while(max_i != 0 )
        {
             pre_jump=0;
             max_i = 0; 
             temp_jump=0;  
            for(int i=index_k+1; i <= index_k+nums[index_k]; i++)
            {
                temp_jump = nums[index_k] + nums[i];
                if (temp_jump > pre_jump)
                {
                    max_i = i;

                }
                pre_jump = temp_jump;
            }
            jump=nums[max_i]+ max_i + 1;
            if(jump >= nums.size())
                return true;
            index_k = max_i;
        }

        return false;        
    }
    bool canJump_greed(vector<int>& nums) 
    {
        if(nums.size() <1 )
            return false;
        int len = nums.size();    
        //贪心算法，更好,注意判断条件
        int reach=0;//记录最远能到达的位置
        for(int i=0;i<len;i++)
        {
            if(reach>=len-1)
                return true;
            if(i>reach)
                return false;
            reach=max(reach,i+nums[i]);//先判断再更新reach的值
        }
        if(reach>=len-1)
            return true;
    }
    int canJump2(vector<int>& nums) 
    {
        if(nums.size() <= 1 )
            return 0;
        int res=0;
        int index_k = 0;
        int pre_jump = 0;
        int temp_jump =0;
        int max_i=1;
        int jump=0;
        int max_jump=0;
        while(max_i != 0 )  //for循环放在外面，while循环放在里面
        {
             pre_jump=0;
             max_i = 0; 
             temp_jump=0;
             max_jump = 0;  
            for(int i=index_k+1; i <= index_k+nums[index_k]; i++)
            {
                temp_jump = i + nums[i];
                if (temp_jump > max_jump)
                {
                    max_i = i;
                    max_jump = temp_jump;

                }
                // pre_jump = temp_jump;
            }
            jump=nums[max_i]+ max_i + 1;
            res++;
            if(jump >= nums.size())
            {
                if(nums[0] >= nums.size()-1)
                    return res;
                else
                    return res+1;
            }
            index_k = max_i;
        }      
    }

};
int main()
{
    vector<int> nums;
    nums = {2,3,1,1,4};
    // nums = {3,2,1,0,4};
    // nums ={1,1,1,0};
    // nums = {2,3,1};
    // nums ={7,0,9,6,9,6,1,7,9,0,1,2,9,0,3};
    // nums = {1,2};
    // nums = {2,1};
    // nums = {6,9,1,5,6,0,0,5,9};
    Solution Sol; 
    int res = Sol.canJump(nums);
    cout << "问题一的解：" << res <<endl;
    res = Sol.canJump_greed(nums);
    cout << "问题一的贪心解法:" << res <<endl;
    res = Sol.canJump2(nums);
    cout << "问题二的贪心解法:" << res <<endl;
    return 0;
}