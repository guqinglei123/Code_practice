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
    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        TreeNode *last_node = NULL;
        TreeNode *res_node;
        if (pRootOfTree == NULL)
            return NULL;
        help(pRootOfTree, &last_node); //是传递last_node的地址，而非直接传递last_node来储存上一个访问的节点
                                       //直接传递的值将会是上一个节点，而不是前一个访问过的节点
        res_node = last_node;
        while (res_node->left != NULL)
        {
            res_node = res_node->left;
        }
        return res_node;
    }

    void help(TreeNode *pRootOfTree, TreeNode **last_node)
    {
        if (pRootOfTree == NULL)
            return;

        help(pRootOfTree->left, last_node);
        //root
        pRootOfTree->left = *last_node;
        if (*last_node != NULL)
            (*last_node)->right = pRootOfTree;

        *last_node = pRootOfTree; //如何去储存最后一个节点

        help(pRootOfTree->right, last_node);
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    void PrintDoubleLinkedList(TreeNode *pHeadOfList)
    {
        TreeNode *pNode = pHeadOfList;

        printf("The nodes from left to right are:\n");
        while (pNode != nullptr)
        {
            printf("%d\t", pNode->val);

            if (pNode->right == nullptr)
                break;
            pNode = pNode->right;
        }

        printf("\nThe nodes from right to left are:\n");
        while (pNode != nullptr)
        {
            printf("%d\t", pNode->val);

            if (pNode->left == nullptr)
                break;
            pNode = pNode->left;
        }

        printf("\n");
    }

    void DestroyList(TreeNode *pHeadOfList)
    {
        TreeNode *pNode = pHeadOfList;
        while (pNode != nullptr)
        {
            TreeNode *pNext = pNode->right;

            delete pNode;
            pNode = pNext;
        }
    }

    void Test(char *testName, TreeNode *pRootOfTree)
    {
        if (testName != nullptr)
            printf("%s begins:\n", testName);

        mytree.PrintTree(pRootOfTree);

        TreeNode *pHeadOfList = Sol.Convert(pRootOfTree);

        PrintDoubleLinkedList(pHeadOfList);
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

        DestroyList(pNode4);
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

        DestroyList(pNode1);
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

        DestroyList(pNode1);
    }

    // Ê÷ÖÐÖ»ÓÐ1¸ö½áµã
    void Test4()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(1);
        Test("Test4", pNode1);

        DestroyList(pNode1);
    }

    // Ê÷ÖÐÃ»ÓÐ½áµã
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