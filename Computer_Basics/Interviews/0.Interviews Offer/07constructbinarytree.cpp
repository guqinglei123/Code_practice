#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
  public:
    TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin)
    {

        if(pre.empty()||vin.empty())
            return NULL;
        // TreeNode_p=&pre[0];
        int *index_pre_start = &pre[0];
        int *index_pre_end = &pre[pre.size() - 1];
        int *index_vin_start = &vin[0];
        int *index_vin_end = &vin[vin.size() - 1];
        return helper(index_pre_start, index_pre_end, index_vin_start, index_vin_end);
    }
    TreeNode* helper(int *index_pre_start, int *index_pre_end, int *index_vin_start, int *index_vin_end)
    {
        TreeNode *root = new TreeNode(*index_pre_start);
        int error_left, error_right;
        int* i;
        for (i = index_vin_start; i <= index_vin_end; i = i + 1)
        {
            if (root->val == (*i))
            {
                error_left = i - index_vin_start;
                error_right = index_vin_end - i;
                if (error_left > 0)
                    root->left= helper(index_pre_start+1,(index_pre_start+error_left),index_vin_start,i-1);
                if (error_left < index_pre_end - index_pre_start)//if (error_right > 0)
                    root->right= helper((index_pre_start+error_left+1),index_pre_end,i+1,index_vin_end);
            }
        }
        return root;

    }
};

int main(int argc, char const *argv[])
{
    /* code */
    vector<int> pre, in;
    pre = {1, 2, 4, 7, 3, 5, 6, 8};
    in = {4, 7, 2, 1, 5, 3, 8, 6};
    Solution Sol;
    TreeNode* res=Sol.reConstructBinaryTree(pre, in);
    return 0;
}
