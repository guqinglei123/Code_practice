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
    bool isSymmetrical(TreeNode *pRoot)
    {
        if (pRoot == NULL)
            return true;
        stack<TreeNode *> tree_stack1;
        stack<TreeNode *> tree_stack2;
        TreeNode *pRoot1;
        TreeNode *pRoot2;
        tree_stack1.push(pRoot);
        tree_stack2.push(pRoot);
        pRoot1 = pRoot;
        pRoot2 = pRoot;
        while ((!tree_stack1.empty()) && (!tree_stack2.empty()))
        {
            while ((pRoot1->left != NULL) && (pRoot2->right != NULL))
            {
                if (pRoot1->left->val != pRoot2->right->val)
                    return false;
                tree_stack1.push(pRoot1->left);
                tree_stack2.push(pRoot2->right);
                pRoot1 = pRoot1->left;
                pRoot2 = pRoot2->right;
                if ((pRoot1->left != NULL) && (pRoot2->right == NULL))
                    return false;
                if ((pRoot1->left == NULL) && (pRoot2->right != NULL))
                    return false;
            }
            pRoot1 = tree_stack1.top();
            tree_stack1.pop();
            pRoot2 = tree_stack2.top();
            tree_stack2.pop();
        }
        if(((tree_stack1.empty()) && (tree_stack2.empty())))
            return true;
        else
            return false;
        return false;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    void Test(char *testName, TreeNode *pRoot, bool expected)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        if (Sol.isSymmetrical(pRoot) == expected)
            printf("Passed.\n");
        else
            printf("FAILED.\n");
    }

    //            8
    //        6      6
    //       5 7    7 5
    void Test1()
    {
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode61 = mytree.CreateTreeNode(6);
        TreeNode *pNode62 = mytree.CreateTreeNode(6);
        TreeNode *pNode51 = mytree.CreateTreeNode(5);
        TreeNode *pNode71 = mytree.CreateTreeNode(7);
        TreeNode *pNode72 = mytree.CreateTreeNode(7);
        TreeNode *pNode52 = mytree.CreateTreeNode(5);

        mytree.ConnectTreeNodes(pNode8, pNode61, pNode62);
        mytree.ConnectTreeNodes(pNode61, pNode51, pNode71);
        mytree.ConnectTreeNodes(pNode62, pNode72, pNode52);

        Test("Test1", pNode8, true);

        mytree.DestroyTree(pNode8);
    }

    //            8
    //        6      9
    //       5 7    7 5
    void Test2()
    {
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode61 = mytree.CreateTreeNode(6);
        TreeNode *pNode9 = mytree.CreateTreeNode(9);
        TreeNode *pNode51 = mytree.CreateTreeNode(5);
        TreeNode *pNode71 = mytree.CreateTreeNode(7);
        TreeNode *pNode72 = mytree.CreateTreeNode(7);
        TreeNode *pNode52 = mytree.CreateTreeNode(5);

        mytree.ConnectTreeNodes(pNode8, pNode61, pNode9);
        mytree.ConnectTreeNodes(pNode61, pNode51, pNode71);
        mytree.ConnectTreeNodes(pNode9, pNode72, pNode52);

        Test("Test2", pNode8, false);

        mytree.DestroyTree(pNode8);
    }

    //            8
    //        6      6
    //       5 7    7
    void Test3()
    {
        TreeNode *pNode8 = mytree.CreateTreeNode(8);
        TreeNode *pNode61 = mytree.CreateTreeNode(6);
        TreeNode *pNode62 = mytree.CreateTreeNode(6);
        TreeNode *pNode51 = mytree.CreateTreeNode(5);
        TreeNode *pNode71 = mytree.CreateTreeNode(7);
        TreeNode *pNode72 = mytree.CreateTreeNode(7);

        mytree.ConnectTreeNodes(pNode8, pNode61, pNode62);
        mytree.ConnectTreeNodes(pNode61, pNode51, pNode71);
        mytree.ConnectTreeNodes(pNode62, pNode72, nullptr);

        Test("Test3", pNode8, false);

        mytree.DestroyTree(pNode8);
    }

    //               5
    //              / \
//             3   3
    //            /     \
//           4       4
    //          /         \
//         2           2
    //        /             \
//       1               1
    void Test4()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode31 = mytree.CreateTreeNode(3);
        TreeNode *pNode32 = mytree.CreateTreeNode(3);
        TreeNode *pNode41 = mytree.CreateTreeNode(4);
        TreeNode *pNode42 = mytree.CreateTreeNode(4);
        TreeNode *pNode21 = mytree.CreateTreeNode(2);
        TreeNode *pNode22 = mytree.CreateTreeNode(2);
        TreeNode *pNode11 = mytree.CreateTreeNode(1);
        TreeNode *pNode12 = mytree.CreateTreeNode(1);

        mytree.ConnectTreeNodes(pNode5, pNode31, pNode32);
        mytree.ConnectTreeNodes(pNode31, pNode41, nullptr);
        mytree.ConnectTreeNodes(pNode32, nullptr, pNode42);
        mytree.ConnectTreeNodes(pNode41, pNode21, nullptr);
        mytree.ConnectTreeNodes(pNode42, nullptr, pNode22);
        mytree.ConnectTreeNodes(pNode21, pNode11, nullptr);
        mytree.ConnectTreeNodes(pNode22, nullptr, pNode12);

        Test("Test4", pNode5, true);

        mytree.DestroyTree(pNode5);
    }

    //               5
    //              / \
//             3   3
    //            /     \
//           4       4
    //          /         \
//         6           2
    //        /             \
//       1               1
    void Test5()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode31 = mytree.CreateTreeNode(3);
        TreeNode *pNode32 = mytree.CreateTreeNode(3);
        TreeNode *pNode41 = mytree.CreateTreeNode(4);
        TreeNode *pNode42 = mytree.CreateTreeNode(4);
        TreeNode *pNode6 = mytree.CreateTreeNode(6);
        TreeNode *pNode22 = mytree.CreateTreeNode(2);
        TreeNode *pNode11 = mytree.CreateTreeNode(1);
        TreeNode *pNode12 = mytree.CreateTreeNode(1);

        mytree.ConnectTreeNodes(pNode5, pNode31, pNode32);
        mytree.ConnectTreeNodes(pNode31, pNode41, nullptr);
        mytree.ConnectTreeNodes(pNode32, nullptr, pNode42);
        mytree.ConnectTreeNodes(pNode41, pNode6, nullptr);
        mytree.ConnectTreeNodes(pNode42, nullptr, pNode22);
        mytree.ConnectTreeNodes(pNode6, pNode11, nullptr);
        mytree.ConnectTreeNodes(pNode22, nullptr, pNode12);

        Test("Test5", pNode5, false);

        mytree.DestroyTree(pNode5);
    }

    //               5
    //              / \
//             3   3
    //            /     \
//           4       4
    //          /         \
//         2           2
    //                      \
//                       1
    void Test6()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode31 = mytree.CreateTreeNode(3);
        TreeNode *pNode32 = mytree.CreateTreeNode(3);
        TreeNode *pNode41 = mytree.CreateTreeNode(4);
        TreeNode *pNode42 = mytree.CreateTreeNode(4);
        TreeNode *pNode21 = mytree.CreateTreeNode(2);
        TreeNode *pNode22 = mytree.CreateTreeNode(2);
        TreeNode *pNode12 = mytree.CreateTreeNode(1);

        mytree.ConnectTreeNodes(pNode5, pNode31, pNode32);
        mytree.ConnectTreeNodes(pNode31, pNode41, nullptr);
        mytree.ConnectTreeNodes(pNode32, nullptr, pNode42);
        mytree.ConnectTreeNodes(pNode41, pNode21, nullptr);
        mytree.ConnectTreeNodes(pNode42, nullptr, pNode22);
        mytree.ConnectTreeNodes(pNode21, nullptr, nullptr);
        mytree.ConnectTreeNodes(pNode22, nullptr, pNode12);

        Test("Test6", pNode5, false);

        mytree.DestroyTree(pNode5);
    }

    // Ö»ÓÐÒ»¸ö½áµã
    void Test7()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(1);
        Test("Test7", pNode1, true);

        mytree.DestroyTree(pNode1);
    }

    // Ã»ÓÐ½áµã
    void Test8()
    {
        Test("Test8", nullptr, true);
    }

    // ËùÓÐ½áµã¶¼ÓÐÏàÍ¬µÄÖµ£¬Ê÷¶Ô³Æ
    //               5
    //              / \
    //             5   5
    //            /     \
    //           5       5
    //          /         \
    //         5           5
    void Test9()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(5);
        TreeNode *pNode21 = mytree.CreateTreeNode(5);
        TreeNode *pNode22 = mytree.CreateTreeNode(5);
        TreeNode *pNode31 = mytree.CreateTreeNode(5);
        TreeNode *pNode32 = mytree.CreateTreeNode(5);
        TreeNode *pNode41 = mytree.CreateTreeNode(5);
        TreeNode *pNode42 = mytree.CreateTreeNode(5);

        mytree.ConnectTreeNodes(pNode1, pNode21, pNode22);
        mytree.ConnectTreeNodes(pNode21, pNode31, nullptr);
        mytree.ConnectTreeNodes(pNode22, nullptr, pNode32);
        mytree.ConnectTreeNodes(pNode31, pNode41, nullptr);
        mytree.ConnectTreeNodes(pNode32, nullptr, pNode42);
        mytree.ConnectTreeNodes(pNode41, nullptr, nullptr);
        mytree.ConnectTreeNodes(pNode42, nullptr, nullptr);

        Test("Test9", pNode1, true);

        mytree.DestroyTree(pNode1);
    }

    // ËùÓÐ½áµã¶¼ÓÐÏàÍ¬µÄÖµ£¬Ê÷²»¶Ô³Æ
    //               5
    //              / \
    //             5   5
    //            /     \
    //           5       5
    //          /       /
    //         5       5
    void Test10()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(5);
        TreeNode *pNode21 = mytree.CreateTreeNode(5);
        TreeNode *pNode22 = mytree.CreateTreeNode(5);
        TreeNode *pNode31 = mytree.CreateTreeNode(5);
        TreeNode *pNode32 = mytree.CreateTreeNode(5);
        TreeNode *pNode41 = mytree.CreateTreeNode(5);
        TreeNode *pNode42 = mytree.CreateTreeNode(5);

        mytree.ConnectTreeNodes(pNode1, pNode21, pNode22);
        mytree.ConnectTreeNodes(pNode21, pNode31, nullptr);
        mytree.ConnectTreeNodes(pNode22, nullptr, pNode32);
        mytree.ConnectTreeNodes(pNode31, pNode41, nullptr);
        mytree.ConnectTreeNodes(pNode32, pNode42, nullptr);
        mytree.ConnectTreeNodes(pNode41, nullptr, nullptr);
        mytree.ConnectTreeNodes(pNode42, nullptr, nullptr);

        Test("Test10", pNode1, false);

        mytree.DestroyTree(pNode1);
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
    test.Test8();
    test.Test9();
    test.Test10();
    return 0;
}