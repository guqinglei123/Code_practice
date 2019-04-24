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
    vector<int> PrintFromTopToBottom(TreeNode *root)
    {
        vector<int> res_vect;
        if (root == NULL)
            return res_vect;
        queue<TreeNode *> deque_tree;
        deque_tree.push(root);
        while (!deque_tree.empty())
        {
            TreeNode *temp = deque_tree.front();
            deque_tree.pop();
            printf("%d\t", temp->val);
            res_vect.push_back(temp->val);
            if (temp->left != NULL)
                deque_tree.push(temp->left);
            if (temp->right != NULL)
                deque_tree.push(temp->right);
        }
        return res_vect;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    void Test(char *testName, TreeNode *pRoot)
    {
        if (testName != nullptr)
            printf("%s begins: \n", testName);

        mytree.PrintTree(pRoot);

        printf("The nodes from top to bottom, from left to right are: \n");
        Sol.PrintFromTopToBottom(pRoot);

        printf("\n\n");
    }

    //            10
    //         /      \
//        6        14
    //       /\        /\
//      4  8     12  16
    void Test1()
    {
        TreeNode *pNode10 = mytree.CreateTreeNode(10);
        TreeNode *pNode6 = mytree.CreateTreeNode(6);
        TreeNode *pNode14 = mytree.CreateTreeNode(14);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode12 = mytree.CreateTreeNode(12);
        TreeNode *pNode16 = mytree.CreateTreeNode(16);

        mytree.ConnectTreeNodes(pNode10, pNode6, pNode14);
        mytree.ConnectTreeNodes(pNode6, pNode4, pNode8);
        mytree.ConnectTreeNodes(pNode14, pNode12, pNode16);

        Test("Test1", pNode10);

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
    void Test2()
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

        Test("Test2", pNode5);

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
    void Test3()
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

        Test("Test3", pNode1);

        mytree.DestroyTree(pNode1);
    }

    // 树中只有1个结点
    void Test4()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(1);
        Test("Test4", pNode1);

        mytree.DestroyTree(pNode1);
    }

    // 树中没有结点
    void Test5()
    {
        Test("Test5", nullptr);
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

    return 0;
}