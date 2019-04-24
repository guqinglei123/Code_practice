#include <vector>
#include <list>
#include <stack>
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
    int minNumberInRotateArray(vector<int> rotateArray)
    {
        if (rotateArray.size() <= 0)
            return 0;
        return helper(0, rotateArray.size() - 1, rotateArray);
    }
    int helper(int left, int right, vector<int> &rotateArray) //对于较多元素相同的情况无法处理
    {

        if (right - left == 1)
            return rotateArray[right];
        int mid = (left + right) / 2;
        // if ((rotateArray[mid] > rotateArray[mid - 1]) && (rotateArray[mid] > rotateArray[mid + 1]))
        //     return rotateArray[mid + 1];
        // else if ((rotateArray[mid] < rotateArray[mid - 1]) && (rotateArray[mid] < rotateArray[mid + 1]))
        //     return rotateArray[mid];
        // else if ((rotateArray[mid] >= rotateArray[mid - 1]) && (rotateArray[mid] <= rotateArray[mid + 1]))
        //     return helper(left, mid - 1, rotateArray);
        // else if ((rotateArray[mid] <= rotateArray[mid - 1]) && (rotateArray[mid] >= rotateArray[mid + 1]))
        //     return helper(mid + 1,right , rotateArray);
        // return 0;
        if((rotateArray[mid] == rotateArray[left])&&(rotateArray[mid] == rotateArray[right]))
            return mininorder(left,right,rotateArray);//特殊情况的处理
        else if ((rotateArray[mid] >= rotateArray[left]))
            return helper(mid , right, rotateArray);
        else if ((rotateArray[mid] <= rotateArray[right]))
            return helper(left, mid, rotateArray);
        return 0;
    }
    int mininorder(int left, int right, vector<int> &rotateArray)
    {
        int temp = rotateArray[left];
        for(int i =left+1;i<=right;i++)
        {
            if(temp > rotateArray[i])
                temp = rotateArray[i];
        }
        return temp;
        
    }
};



int main(int argc, char const *argv[])
{
    /* code */
    // int a[] = {
    //     2,
    //     1,
    //     2,
    //     2,
    //     2,
    // };
    int a[] = {
        3,
        4,
        5,
        1,
        2,
    };
    vector<int> vec(a, a + 5);

    Solution solu;
    cout << solu.minNumberInRotateArray(vec) << endl;
    return 0;
}
