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
#include <cstring>
#include "mybinarytree.h"
using namespace std;
class Solution
{
  public:
    void MirrorRecursively(TreeNode *pRoot)
    {
        if (pRoot == NULL)
            return;

        TreeNode *tree_temp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tree_temp;
        MirrorRecursively(pRoot->left);
        MirrorRecursively(pRoot->right);
    }
    void MirrorIteratively(TreeNode *pRoot)
    {
        if (pRoot == NULL)
            return;
        stack<TreeNode *> tree_stack;
        tree_stack.push(pRoot);
        while (tree_stack.top() != NULL)
        {
            while (pRoot != NULL)
            {
                TreeNode *tree_temp = pRoot->left;
                pRoot->left = pRoot->right;
                pRoot->right = tree_temp;
                tree_stack.push(pRoot->right);
                pRoot = pRoot->left;
            }
            pRoot = tree_stack.top();
            tree_stack.pop();
        }
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    void Test1()
    {
        printf("=====Test1 starts:=====\n");
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

        mytree.PrintTree(pNode8);

        printf("=====Test1: Sol.MirrorRecursively=====\n");
        Sol.MirrorRecursively(pNode8);
        mytree.PrintTree(pNode8);

        printf("=====Test1: Sol.MirrorIteratively=====\n");
        Sol.MirrorIteratively(pNode8);
        mytree.PrintTree(pNode8);

        mytree.DestroyTree(pNode8);
    }

    // ²âÊÔ¶þ²æÊ÷£º³öÒ¶×Ó½áµãÖ®Íâ£¬×óÓÒµÄ½áµã¶¼ÓÐÇÒÖ»ÓÐÒ»¸ö×ó×Ó½áµã
    //            8
    //          7
    //        6
    //      5
    //    4
    void Test2()
    {
        printf("=====Test2 starts:=====\n");
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode7 = mytree.CreateTreeNode(7);
        TreeNode *pNode6 = mytree.CreateTreeNode(6);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);

        mytree.ConnectTreeNodes(pNode8, pNode7, nullptr);
        mytree.ConnectTreeNodes(pNode7, pNode6, nullptr);
        mytree.ConnectTreeNodes(pNode6, pNode5, nullptr);
        mytree.ConnectTreeNodes(pNode5, pNode4, nullptr);

        mytree.PrintTree(pNode8);

        printf("=====Test2: Sol.MirrorRecursively=====\n");
        Sol.MirrorRecursively(pNode8);
        mytree.PrintTree(pNode8);

        printf("=====Test2: Sol.MirrorIteratively=====\n");
        Sol.MirrorIteratively(pNode8);
        mytree.PrintTree(pNode8);

        mytree.DestroyTree(pNode8);
    }

    // ²âÊÔ¶þ²æÊ÷£º³öÒ¶×Ó½áµãÖ®Íâ£¬×óÓÒµÄ½áµã¶¼ÓÐÇÒÖ»ÓÐÒ»¸öÓÒ×Ó½áµã
    //            8
    //             7
    //              6
    //               5
    //                4
    void Test3()
    {
        printf("=====Test3 starts:=====\n");
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode7 = mytree.CreateTreeNode(7);
        TreeNode *pNode6 = mytree.CreateTreeNode(6);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode4 = mytree.CreateTreeNode(4);

        mytree.ConnectTreeNodes(pNode8, nullptr, pNode7);
        mytree.ConnectTreeNodes(pNode7, nullptr, pNode6);
        mytree.ConnectTreeNodes(pNode6, nullptr, pNode5);
        mytree.ConnectTreeNodes(pNode5, nullptr, pNode4);

        mytree.PrintTree(pNode8);

        printf("=====Test3: Sol.MirrorRecursively=====\n");
        Sol.MirrorRecursively(pNode8);
        mytree.PrintTree(pNode8);

        printf("=====Test3: Sol.MirrorIteratively=====\n");
        Sol.MirrorIteratively(pNode8);
        mytree.PrintTree(pNode8);

        mytree.DestroyTree(pNode8);
    }

    // ²âÊÔ¿Õ¶þ²æÊ÷£º¸ù½áµãÎª¿ÕÖ¸Õë
    void Test4()
    {
        printf("=====Test4 starts:=====\n");
        TreeNode *pNode = nullptr;

        mytree.PrintTree(pNode);

        printf("=====Test4: Sol.MirrorRecursively=====\n");
        Sol.MirrorRecursively(pNode);
        mytree.PrintTree(pNode);

        printf("=====Test4: Sol.MirrorIteratively=====\n");
        Sol.MirrorIteratively(pNode);
        mytree.PrintTree(pNode);
    }

    // ²âÊÔÖ»ÓÐÒ»¸ö½áµãµÄ¶þ²æÊ÷
    void Test5()
    {
        printf("=====Test5 starts:=====\n");
        TreeNode *pNode8 = mytree.CreateTreeNode(8);

        mytree.PrintTree(pNode8);

        printf("=====Test4: Sol.MirrorRecursively=====\n");
        Sol.MirrorRecursively(pNode8);
        mytree.PrintTree(pNode8);

        printf("=====Test4: Sol.MirrorIteratively=====\n");
        Sol.MirrorIteratively(pNode8);
        mytree.PrintTree(pNode8);
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