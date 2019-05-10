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
#include "mytree.h"
using namespace std;

class Solution
{
  public:
    TreeLinkNode *GetNext(TreeLinkNode *pNode)
    {

        TreeLinkNode *tree_res = new TreeLinkNode(0);
        TreeLinkNode *tree_temp = NULL;
        if ((pNode->right != NULL)) //???
        {
            tree_temp = pNode->right;
            while (tree_temp->left != NULL)
                tree_temp = tree_temp->left;
            tree_res = tree_temp;
        }
        else if ((pNode->right == NULL) && (pNode->left != NULL))
        {
            tree_res = pNode->next;
        }
        else if ((pNode->right == NULL) && (pNode->left == NULL))
        {

            if (pNode->next == NULL)
                return NULL;
            else
            {
                if ((pNode->next)->left == pNode)
                    tree_res = pNode->next;
                else if ((pNode->next)->right == pNode)//?????????????
                {
                    if ((pNode->next->next)->right == pNode->next)
                        return NULL;
                    else if((pNode->next->next)->left == pNode->next)
                        tree_res = pNode->next->next;
                }
            }
        }
        return tree_res;
    }
};

class Test_Solution
{
  public:
    MyTree mytree;
    Solution Sol;
    void Test(char *testName, TreeLinkNode *pNode, TreeLinkNode *expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        TreeLinkNode *pNext = Sol.GetNext(pNode);
        if (pNext == expected)
            printf("Passed.\n");
        else
            printf("FAILED.\n");
    }

    //            8
    //        6      10
    //       5 7    9  11
    void Test1_7()
    {
        TreeLinkNode *pNode8 = mytree.CreateTreeLinkNode(8);
        TreeLinkNode *pNode6 = mytree.CreateTreeLinkNode(6);
        TreeLinkNode *pNode10 = mytree.CreateTreeLinkNode(10);
        TreeLinkNode *pNode5 = mytree.CreateTreeLinkNode(5);
        TreeLinkNode *pNode7 = mytree.CreateTreeLinkNode(7);
        TreeLinkNode *pNode9 = mytree.CreateTreeLinkNode(9);
        TreeLinkNode *pNode11 = mytree.CreateTreeLinkNode(11);

        mytree.ConnectTreeNodes(pNode8, pNode6, pNode10);
        mytree.ConnectTreeNodes(pNode6, pNode5, pNode7);
        mytree.ConnectTreeNodes(pNode10, pNode9, pNode11);

        Test("Test1", pNode8, pNode9);
        Test("Test2", pNode6, pNode7);
        Test("Test3", pNode10, pNode11);
        Test("Test4", pNode5, pNode6);
        Test("Test5", pNode7, pNode8);
        Test("Test6", pNode9, pNode10);
        Test("Test7", pNode11, nullptr);

        mytree.DestroyTree(pNode8);
    }

    //            5
    //          4
    //        3
    //      2
    void Test8_11()
    {
        TreeLinkNode *pNode5 = mytree.CreateTreeLinkNode(5);
        TreeLinkNode *pNode4 = mytree.CreateTreeLinkNode(4);
        TreeLinkNode *pNode3 = mytree.CreateTreeLinkNode(3);
        TreeLinkNode *pNode2 = mytree.CreateTreeLinkNode(2);

        mytree.ConnectTreeNodes(pNode5, pNode4, nullptr);
        mytree.ConnectTreeNodes(pNode4, pNode3, nullptr);
        mytree.ConnectTreeNodes(pNode3, pNode2, nullptr);

        Test("Test8", pNode5, nullptr);
        Test("Test9", pNode4, pNode5);
        Test("Test10", pNode3, pNode4);
        Test("Test11", pNode2, pNode3);

        mytree.DestroyTree(pNode5);
    }

    //        2
    //         3
    //          4
    //           5
    void Test12_15()
    {
        TreeLinkNode *pNode2 = mytree.CreateTreeLinkNode(2);
        TreeLinkNode *pNode3 = mytree.CreateTreeLinkNode(3);
        TreeLinkNode *pNode4 = mytree.CreateTreeLinkNode(4);
        TreeLinkNode *pNode5 = mytree.CreateTreeLinkNode(5);

        mytree.ConnectTreeNodes(pNode2, nullptr, pNode3);
        mytree.ConnectTreeNodes(pNode3, nullptr, pNode4);
        mytree.ConnectTreeNodes(pNode4, nullptr, pNode5);

        Test("Test12", pNode5, nullptr);
        Test("Test13", pNode4, pNode5);
        Test("Test14", pNode3, pNode4);
        Test("Test15", pNode2, pNode3);

        mytree.DestroyTree(pNode2);
    } 

    void Test16()
    {
        TreeLinkNode *pNode5 = mytree.CreateTreeLinkNode(5);

        Test("Test16", pNode5, nullptr);

        mytree.DestroyTree(pNode5);
    }
};

int main(int argc, char *argv[])
{
    Test_Solution test;
    test.Test1_7();
    test.Test8_11();
    test.Test12_15();
    test.Test16();
    return 0;
}