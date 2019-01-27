#include <stdio.h>
#include <stdlib.h>
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
class MyTree
{
  public:
    TreeLinkNode* CreateTreeLinkNode(int value)
{
    TreeLinkNode* pNode = new TreeLinkNode(0);
    pNode->val = value;
    pNode->left = nullptr;
    pNode->right = nullptr;
    pNode->next = nullptr;

    return pNode;
}

void ConnectTreeNodes(TreeLinkNode* pParent, TreeLinkNode* pLeft, TreeLinkNode* pRight)
{
    if(pParent != nullptr)
    {
        pParent->left = pLeft;
        pParent->right = pRight;

        if(pLeft != nullptr)
            pLeft->next = pParent;
        if(pRight != nullptr)
            pRight->next = pParent;
    }
}

void PrintTreeNode(TreeLinkNode* pNode)
{
    if(pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->val);

        if(pNode->left != nullptr)
            printf("value of its left child is: %d.\n", pNode->left->val);
        else
            printf("left child is null.\n");

        if(pNode->right != nullptr)
            printf("value of its right child is: %d.\n", pNode->right->val);
        else
            printf("right child is null.\n");
    }
    else
    {
        printf("this node is null.\n");
    }

    printf("\n");
}

void PrintTree(TreeLinkNode* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != nullptr)
    {
        if(pRoot->left != nullptr)
            PrintTree(pRoot->left);

        if(pRoot->right != nullptr)
            PrintTree(pRoot->right);
    }
}

void DestroyTree(TreeLinkNode* pRoot)
{
    if(pRoot != nullptr)
    {
        TreeLinkNode* pLeft = pRoot->left;
        TreeLinkNode* pRight = pRoot->right;

        delete pRoot;
        pRoot = nullptr;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}

};
