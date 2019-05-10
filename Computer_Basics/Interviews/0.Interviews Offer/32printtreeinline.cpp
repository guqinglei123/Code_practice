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
#include "mybinarytree.h"
using namespace std;
class Solution
{
  public:
    vector<vector<int> >  PrintTreeInLine(TreeNode *root)
    {
        vector<vector<int>> res_vect;
        vector<int> temp_vect;
        if (root == NULL)
            return res_vect;
        queue<TreeNode *> deque_tree;
        int curren_level,next_level;
        deque_tree.push(root);
        curren_level = 1;
        next_level = 0;
        while (!deque_tree.empty())
        {
            TreeNode *temp = deque_tree.front();
            deque_tree.pop();
            curren_level--;
            printf("%d\t", temp->val);
            temp_vect.push_back(temp->val);
            if (temp->left != NULL)
            {
                deque_tree.push(temp->left);
                next_level++;
            }

            if (temp->right != NULL)
            {
                deque_tree.push(temp->right);
                next_level++;
            }

            if(curren_level == 0)
            {
                curren_level = next_level;
                next_level =0;
                res_vect.push_back(temp_vect);
                temp_vect.clear();
                printf("\n");
            }
                
        }
        return res_vect;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    void Test1()
    {
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode6 = mytree.CreateTreeNode(6);
        TreeNode *pNode10 = mytree.CreateTreeNode(10);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode7 = mytree.CreateTreeNode(7);
        TreeNode *pNode9 = mytree.CreateTreeNode(9);
        TreeNode *pNode11 = mytree.CreateTreeNode(11);

        mytree.ConnectTreeNodes(pNode8, pNode6, pNode10);
        mytree.ConnectTreeNodes(pNode6, pNode5, pNode7);
        mytree.ConnectTreeNodes(pNode10, pNode9, pNode11);

        printf("====Test1 Begins: ====\n");
        printf("Expected Result is:\n");
        printf("8 \n");
        printf("6 10 \n");
        printf("5 7 9 11 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInLine(pNode8);
        printf("\n");

        mytree.DestroyTree(pNode8);
    }

    //            5
    //          4
    //        3
    //      2
    void Test2()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode3 = mytree.CreateTreeNode(3);
        TreeNode *pNode2 = mytree.CreateTreeNode(2);

        mytree.ConnectTreeNodes(pNode5, pNode4, nullptr);
        mytree.ConnectTreeNodes(pNode4, pNode3, nullptr);
        mytree.ConnectTreeNodes(pNode3, pNode2, nullptr);

        printf("====Test2 Begins: ====\n");
        printf("Expected Result is:\n");
        printf("5 \n");
        printf("4 \n");
        printf("3 \n");
        printf("2 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInLine(pNode5);
        printf("\n");

        mytree.DestroyTree(pNode5);
    }

    //        5
    //         4
    //          3
    //           2
    void Test3()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode3 = mytree.CreateTreeNode(3);
        TreeNode *pNode2 = mytree.CreateTreeNode(2);

        mytree.ConnectTreeNodes(pNode5, nullptr, pNode4);
        mytree.ConnectTreeNodes(pNode4, nullptr, pNode3);
        mytree.ConnectTreeNodes(pNode3, nullptr, pNode2);

        printf("====Test3 Begins: ====\n");
        printf("Expected Result is:\n");
        printf("5 \n");
        printf("4 \n");
        printf("3 \n");
        printf("2 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInLine(pNode5);
        printf("\n");

        mytree.DestroyTree(pNode5);
    }

    void Test4()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);

        printf("====Test4 Begins: ====\n");
        printf("Expected Result is:\n");
        printf("5 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInLine(pNode5);
        printf("\n");

        mytree.DestroyTree(pNode5);
    }

    void Test5()
    {
        printf("====Test5 Begins: ====\n");
        printf("Expected Result is:\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInLine(nullptr);
        printf("\n");
    }

    //        100
    //        /
    //       50
    //         \
//         150
    void Test6()
    {
        TreeNode *pNode100 = mytree.CreateTreeNode(100);
        TreeNode *pNode50 = mytree.CreateTreeNode(50);
        TreeNode *pNode150 = mytree.CreateTreeNode(150);

        mytree.ConnectTreeNodes(pNode100, pNode50, nullptr);
        mytree.ConnectTreeNodes(pNode50, nullptr, pNode150);

        printf("====Test6 Begins: ====\n");
        printf("Expected Result is:\n");
        printf("100 \n");
        printf("50 \n");
        printf("150 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInLine(pNode100);
        printf("\n");
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