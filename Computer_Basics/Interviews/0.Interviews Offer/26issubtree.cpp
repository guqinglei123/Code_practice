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
#include "mybinarytree.h"
using namespace std;
class Solution
{
  public:
    bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
    {
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mybinarytree;
    void Test(char *testName, TreeNode *pRoot1, TreeNode *pRoot2, bool expected)
    {
        if (Sol.HasSubtree(pRoot1, pRoot2) == expected)
            printf("%s passed.\n", testName);
        else
            printf("%s failed.\n", testName);
    }

    // Ê÷ÖÐ½áµãº¬ÓÐ·Ö²æ£¬Ê÷BÊÇÊ÷AµÄ×Ó½á¹¹
    //                  8                8
    //              /       \           / \
//             8         7         9   2
    //           /   \
//          9     2
    //               / \
//              4   7
    void Test1()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(7);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA5 = mybinarytree.CreateTreeNode(2);
        TreeNode *pNodeA6 = mybinarytree.CreateTreeNode(4);
        TreeNode *pNodeA7 = mybinarytree.CreateTreeNode(7);

        mybinarytree.ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
        mybinarytree.ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
        mybinarytree.ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

        Test("Test1", pNodeA1, pNodeB1, true);

        mybinarytree.DestroyTree(pNodeA1);
        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷ÖÐ½áµãº¬ÓÐ·Ö²æ£¬Ê÷B²»ÊÇÊ÷AµÄ×Ó½á¹¹
    //                  8                8
    //              /       \           / \
//             8         7         9   2
    //           /   \
//          9     3
    //               / \
//              4   7
    void Test2()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(7);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA5 = mybinarytree.CreateTreeNode(3);
        TreeNode *pNodeA6 = mybinarytree.CreateTreeNode(4);
        TreeNode *pNodeA7 = mybinarytree.CreateTreeNode(7);

        mybinarytree.ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
        mybinarytree.ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
        mybinarytree.ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

        Test("Test2", pNodeA1, pNodeB1, false);

        mybinarytree.DestroyTree(pNodeA1);
        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷ÖÐ½áµãÖ»ÓÐ×ó×Ó½áµã£¬Ê÷BÊÇÊ÷AµÄ×Ó½á¹¹
    //                8                  8
    //              /                   /
    //             8                   9
    //           /                    /
    //          9                    2
    //         /
    //        2
    //       /
    //      5
    void Test3()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(2);
        TreeNode *pNodeA5 = mybinarytree.CreateTreeNode(5);

        mybinarytree.ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

        Test("Test3", pNodeA1, pNodeB1, true);

        mybinarytree.DestroyTree(pNodeA1);
        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷ÖÐ½áµãÖ»ÓÐ×ó×Ó½áµã£¬Ê÷B²»ÊÇÊ÷AµÄ×Ó½á¹¹
    //                8                  8
    //              /                   /
    //             8                   9
    //           /                    /
    //          9                    3
    //         /
    //        2
    //       /
    //      5
    void Test4()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(2);
        TreeNode *pNodeA5 = mybinarytree.CreateTreeNode(5);

        mybinarytree.ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(3);

        mybinarytree.ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
        mybinarytree.ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

        Test("Test4", pNodeA1, pNodeB1, false);

        mybinarytree.DestroyTree(pNodeA1);
        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷ÖÐ½áµãÖ»ÓÐÓÒ×Ó½áµã£¬Ê÷BÊÇÊ÷AµÄ×Ó½á¹¹
    //       8                   8
    //        \                   \ 
//         8                   9
    //          \                   \
//           9                   2
    //            \      
//             2
    //              \
//               5
    void Test5()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(2);
        TreeNode *pNodeA5 = mybinarytree.CreateTreeNode(5);

        mybinarytree.ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
        mybinarytree.ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
        mybinarytree.ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
        mybinarytree.ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
        mybinarytree.ConnectTreeNodes(pNodeB2, nullptr, pNodeB3);

        Test("Test5", pNodeA1, pNodeB1, true);

        mybinarytree.DestroyTree(pNodeA1);
        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷AÖÐ½áµãÖ»ÓÐÓÒ×Ó½áµã£¬Ê÷B²»ÊÇÊ÷AµÄ×Ó½á¹¹
    //       8                   8
    //        \                   \ 
//         8                   9
    //          \                 / \
//           9               3   2
    //            \      
//             2
    //              \
//               5
    void Test6()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(2);
        TreeNode *pNodeA5 = mybinarytree.CreateTreeNode(5);

        mybinarytree.ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
        mybinarytree.ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
        mybinarytree.ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
        mybinarytree.ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(3);
        TreeNode *pNodeB4 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
        mybinarytree.ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

        Test("Test6", pNodeA1, pNodeB1, false);

        mybinarytree.DestroyTree(pNodeA1);
        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷AÎª¿ÕÊ÷
    void Test7()
    {
        TreeNode *pNodeB1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeB2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeB3 = mybinarytree.CreateTreeNode(3);
        TreeNode *pNodeB4 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
        mybinarytree.ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

        Test("Test7", nullptr, pNodeB1, false);

        mybinarytree.DestroyTree(pNodeB1);
    }

    // Ê÷BÎª¿ÕÊ÷
    void Test8()
    {
        TreeNode *pNodeA1 = mybinarytree.CreateTreeNode(8);
        TreeNode *pNodeA2 = mybinarytree.CreateTreeNode(9);
        TreeNode *pNodeA3 = mybinarytree.CreateTreeNode(3);
        TreeNode *pNodeA4 = mybinarytree.CreateTreeNode(2);

        mybinarytree.ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
        mybinarytree.ConnectTreeNodes(pNodeA2, pNodeA3, pNodeA4);

        Test("Test8", pNodeA1, nullptr, false);

        mybinarytree.DestroyTree(pNodeA1);
    }

    // Ê÷AºÍÊ÷B¶¼Îª¿Õ
    void Test9()
    {
        Test("Test9", nullptr, nullptr, false);
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

    return 0;
}