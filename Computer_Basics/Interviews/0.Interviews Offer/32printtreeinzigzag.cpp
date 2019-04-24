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
    vector<vector<int>> PrintTreeInzigzag(TreeNode *root)
    {
        vector<vector<int>> res_vect;
        vector<int> temp_vect;
        if (root == NULL)
            return res_vect;
        queue<TreeNode *> deque_tree;
        stack<int> stack_tree;
        int curren_level, next_level, num_level;
        deque_tree.push(root);
        curren_level = 1;
        next_level = 0;
        num_level = 0;
        TreeNode *temp;
        while (!deque_tree.empty())
        {

            temp = deque_tree.front();
            deque_tree.pop();
            curren_level--;
            if (num_level & 0x01) //奇数
            {
                stack_tree.push(temp->val);
            }
            else //偶数
            {
                printf("%d\t", temp->val);
                temp_vect.push_back(temp->val);
            }

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

            if (curren_level == 0)
            {
                if (num_level & 0x01) //奇数
                {
                    while (!stack_tree.empty())
                    {
                        printf("%d\t", stack_tree.top());
                        temp_vect.push_back(stack_tree.top());
                        stack_tree.pop();
                    }
                }
                num_level++;
                curren_level = next_level;
                next_level = 0;
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
        printf("10 6 \n");
        printf("5 7 9 11 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInzigzag(pNode8);
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
        Sol.PrintTreeInzigzag(pNode5);
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
        Sol.PrintTreeInzigzag(pNode5);
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
        Sol.PrintTreeInzigzag(pNode5);
        printf("\n");

        mytree.DestroyTree(pNode5);
    }

    void Test5()
    {
        printf("====Test5 Begins: ====\n");
        printf("Expected Result is:\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInzigzag(nullptr);
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
        Sol.PrintTreeInzigzag(pNode100);
        printf("\n");
    }

    //                8
    //        4              12
    //     2     6       10      14
    //   1  3  5  7     9 11   13  15
    void Test7()
    {
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode12 = mytree.CreateTreeNode(12);
        TreeNode *pNode2 = mytree.CreateTreeNode(2);
        TreeNode *pNode6 = mytree.CreateTreeNode(6);
        TreeNode *pNode10 = mytree.CreateTreeNode(10);
        TreeNode *pNode14 = mytree.CreateTreeNode(14);
        TreeNode *pNode1 = mytree.CreateTreeNode(1);
        TreeNode *pNode3 = mytree.CreateTreeNode(3);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode7 = mytree.CreateTreeNode(7);
        TreeNode *pNode9 = mytree.CreateTreeNode(9);
        TreeNode *pNode11 = mytree.CreateTreeNode(11);
        TreeNode *pNode13 = mytree.CreateTreeNode(13);
        TreeNode *pNode15 = mytree.CreateTreeNode(15);

        mytree.ConnectTreeNodes(pNode8, pNode4, pNode12);
        mytree.ConnectTreeNodes(pNode4, pNode2, pNode6);
        mytree.ConnectTreeNodes(pNode12, pNode10, pNode14);
        mytree.ConnectTreeNodes(pNode2, pNode1, pNode3);
        mytree.ConnectTreeNodes(pNode6, pNode5, pNode7);
        mytree.ConnectTreeNodes(pNode10, pNode9, pNode11);
        mytree.ConnectTreeNodes(pNode14, pNode13, pNode15);

        printf("====Test7 Begins: ====\n");
        printf("Expected Result is:\n");
        printf("8 \n");
        printf("12 4 \n");
        printf("2 6 10 14 \n");
        printf("15 13 11 9 7 5 3 1 \n\n");

        printf("Actual Result is: \n");
        Sol.PrintTreeInzigzag(pNode8);
        printf("\n");

        mytree.DestroyTree(pNode8);
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
    test.Test7();

    return 0;
}