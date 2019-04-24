#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
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
    char *Serialize(TreeNode *root)
    {

        string str;
        Serialize_core(root, str);
        char *res = new char[str.length() + 1]; //处理返回值的方法
        for (int i = 0; i < str.length(); i++)
            res[i] = str[i];
        res[str.length()] = '\0';
        return res;
    }
    void Serialize_core(TreeNode *root, string &str)
    {
        if (root == NULL)
        {
            str += "$,";
            return;
        }
        str += to_string(root->val);
        str += ',';
        Serialize_core(root->left, str);
        Serialize_core(root->right, str);
    }
    TreeNode *Deserialize(char *str)
    {

        if (str == NULL)
            return NULL;
        TreeNode *res = Deserialize_core(&str);
        return res;
    }
    TreeNode *Deserialize_core(char **str)
    {
        if (**str == '$') //由于递归时，会不断的向后读取字符串
        {                 //所以一定要用**str,
            ++(*str);     //以保证得到递归后指针str指向未被读取的字符
            ++(*str);
            return NULL;
        }
        int num = 0;
        while (**str != '\0' && **str != ',')
        {
            num = num * 10 + ((**str) - '0');
            ++(*str);
        }
        TreeNode *root = new TreeNode(num);
        if (**str == '\0')
            return root;
        else
            (*str)++;
        root->left = Deserialize_core(str);
        root->right = Deserialize_core(str);
        return root;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyBinaryTree mytree;
    bool isSameTree(const TreeNode *pRoot1, const TreeNode *pRoot2)
    {
        if (pRoot1 == nullptr && pRoot2 == nullptr)
            return true;

        if (pRoot1 == nullptr || pRoot2 == nullptr)
            return false;

        if (pRoot1->val != pRoot2->val)
            return false;

        return isSameTree(pRoot1->left, pRoot2->left) &&
               isSameTree(pRoot1->right, pRoot2->right);
    }

    void Test(const char *testName, TreeNode *pRoot)
    {
        if (testName != nullptr)
            printf("%s begins: \n", testName);

        mytree.PrintTree(pRoot);
        char *res = NULL;
        res = Sol.Serialize(pRoot);

        TreeNode *pNewRoot = nullptr;
        pNewRoot = Sol.Deserialize(res);
        mytree.PrintTree(pNewRoot);

        if (isSameTree(pRoot, pNewRoot))
            printf("The deserialized tree is same as the oritinal tree.\n\n");
        else
            printf("The deserialized tree is NOT same as the oritinal tree.\n\n");

        mytree.DestroyTree(pNewRoot);
    }

    //            8
    //        6      10
    //       5 7    9  11
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

        Test("Test1", pNode8);

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

        Test("Test2", pNode5);

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

        Test("Test3", pNode5);

        mytree.DestroyTree(pNode5);
    }

    void Test4()
    {
        TreeNode *pNode5 = mytree.CreateTreeNode(5);

        Test("Test4", pNode5);

        mytree.DestroyTree(pNode5);
    }

    void Test5()
    {
        Test("Test5", nullptr);
    }

    //        5
    //         5
    //          5
    //         5
    //        5
    //       5 5
    //      5   5
    void Test6()
    {
        TreeNode *pNode1 = mytree.CreateTreeNode(5);
        TreeNode *pNode2 = mytree.CreateTreeNode(5);
        TreeNode *pNode3 = mytree.CreateTreeNode(5);
        TreeNode *pNode4 = mytree.CreateTreeNode(5);
        TreeNode *pNode5 = mytree.CreateTreeNode(5);
        TreeNode *pNode61 = mytree.CreateTreeNode(5);
        TreeNode *pNode62 = mytree.CreateTreeNode(5);
        TreeNode *pNode71 = mytree.CreateTreeNode(5);
        TreeNode *pNode72 = mytree.CreateTreeNode(5);

        mytree.ConnectTreeNodes(pNode1, nullptr, pNode2);
        mytree.ConnectTreeNodes(pNode2, nullptr, pNode3);
        mytree.ConnectTreeNodes(pNode3, pNode4, nullptr);
        mytree.ConnectTreeNodes(pNode4, pNode5, nullptr);
        mytree.ConnectTreeNodes(pNode5, pNode61, pNode62);
        mytree.ConnectTreeNodes(pNode61, pNode71, nullptr);
        mytree.ConnectTreeNodes(pNode62, nullptr, pNode72);

        Test("Test6", pNode1);

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

    return 0;
}