#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cstring>
using namespace std;
#include "mybinarytree.h"
class Solution
{
  public:
    vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
    {
        vector<vector<int>> res_vect;
        vector<int> path_vect;
        if (root == NULL)
            return res_vect;
        help(root, expectNumber, path_vect, 0,res_vect);
        return res_vect;
    }
    void help(TreeNode *root, int expectNumber, vector<int> &path_vect, int pre_sum, vector<vector<int>> &res_vect)
    {
        if (root == NULL)//
            return;
        pre_sum = pre_sum + root->val;
        path_vect.push_back(root->val);

        if (pre_sum > expectNumber)
        {
            path_vect.pop_back(); //注意如果该路径点不行，需要删除该路径点
            return;
        }
        else if ((pre_sum == expectNumber)&&(root->right ==NULL)&&(root->left ==NULL))
        {
            //打印
            res_vect.push_back(path_vect);
            auto it = path_vect.begin();
            for (; it != path_vect.end(); it++)
                printf("%d\t", *it);
            printf("\n");
        }
        else 
        {
            help(root->left, expectNumber, path_vect, pre_sum,res_vect);
            help(root->right, expectNumber, path_vect, pre_sum,res_vect);            
        }
        path_vect.pop_back(); //注意如果离开该路径点，需要删除该路径点
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    void Test(char *testName, TreeNode *pRoot, int expectedSum)
    {
        if (testName != nullptr)
            printf("%s begins:\n", testName);

        Sol.FindPath(pRoot, expectedSum);

        printf("\n");
    }

    //            10
    //         /      \
    //        5        12
    //       /\        
    //      4  7
    // ÓÐÁ½ÌõÂ·¾¶ÉÏµÄ½áµãºÍÎª22
    void Test1()
    {
        TreeNode *pNode10 = mytree.CreateTreeNode(10);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode12 = mytree.CreateTreeNode(12);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode7 = mytree.CreateTreeNode(7);

        mytree.ConnectTreeNodes(pNode10, pNode5, pNode12);
        mytree.ConnectTreeNodes(pNode5, pNode4, pNode7);

        printf("Two paths should be found in Test1.\n");
        Test("Test1", pNode10, 22);

        mytree.DestroyTree(pNode10);
    }

    //            10
    //         /      \
    //        5        12
    //       /\        
    //      4  7
    // Ã»ÓÐÂ·¾¶ÉÏµÄ½áµãºÍÎª15
    void Test2()
    {
        TreeNode *pNode10 = mytree.CreateTreeNode(10);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode12 = mytree.CreateTreeNode(12);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode7 = mytree.CreateTreeNode(7);

        mytree.ConnectTreeNodes(pNode10, pNode5, pNode12);
        mytree.ConnectTreeNodes(pNode5, pNode4, pNode7);

        printf("No paths should be found in Test2.\n");
        Test("Test2", pNode10, 15);

        mytree.DestroyTree(pNode10);
    }

    //               5
    //              /
    //             4
    //            /
    //           3
    //          /
    //         2
    //        /
    //       1
    // ÓÐÒ»ÌõÂ·¾¶ÉÏÃæµÄ½áµãºÍÎª15
    void Test3()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode3 = mytree.CreateTreeNode(3);
        TreeNode *pNode2 = mytree.CreateTreeNode(2);
        TreeNode *pNode1 = mytree.CreateTreeNode(1);

        mytree.ConnectTreeNodes(pNode5, pNode4, nullptr);
        mytree.ConnectTreeNodes(pNode4, pNode3, nullptr);
        mytree.ConnectTreeNodes(pNode3, pNode2, nullptr);
        mytree.ConnectTreeNodes(pNode2, pNode1, nullptr);

        printf("One path should be found in Test3.\n");
        Test("Test3", pNode5, 15);

        mytree.DestroyTree(pNode5);
    }

    // 1
    //  \
    //   2
    //    \
    //     3
    //      \
    //       4
    //        \
    //         5
    // Ã»ÓÐÂ·¾¶ÉÏÃæµÄ½áµãºÍÎª16
    void Test4()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(1);
        TreeNode *pNode2 = mytree.CreateTreeNode(2);
        TreeNode *pNode3 = mytree.CreateTreeNode(3);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);

        mytree.ConnectTreeNodes(pNode1, nullptr, pNode2);
        mytree.ConnectTreeNodes(pNode2, nullptr, pNode3);
        mytree.ConnectTreeNodes(pNode3, nullptr, pNode4);
        mytree.ConnectTreeNodes(pNode4, nullptr, pNode5);

        printf("No paths should be found in Test4.\n");
        Test("Test4", pNode1, 16);

        mytree.DestroyTree(pNode1);
    }

    // Ê÷ÖÐÖ»ÓÐ1¸ö½áµã
    void Test5()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(1);

        printf("One path should be found in Test5.\n");
        Test("Test5", pNode1, 1);

        mytree.DestroyTree(pNode1);
    }

    // Ê÷ÖÐÃ»ÓÐ½áµã
    void Test6()
    {
        printf("No paths should be found in Test6.\n");
        Test("Test6", nullptr, 0);
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

    return 0;
}