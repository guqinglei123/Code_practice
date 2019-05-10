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

struct RandomListNode
{
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL)
    {
    }
};

class Solution
{
  public:
    RandomListNode *Clone(RandomListNode *pHead)
    {
        RandomListNode *res_pHead = pHead;
        if (pHead != NULL)
        {
            clonenextnode(pHead);
            clonerandomnode(pHead);
            res_pHead = pHead->next;
            detachlist(pHead);
        }
        return res_pHead;
    }
    void clonenextnode(RandomListNode *pHead)
    {
        RandomListNode *pnode = pHead;
        while (pnode != NULL)
        {
            RandomListNode *newnode = new RandomListNode(pnode->label);
            newnode->next = pnode->next;
            pnode->next = newnode;
            pnode = newnode->next;
        }
    }
    void clonerandomnode(RandomListNode *pHead)
    {
        RandomListNode *pnode = pHead;
        while (pnode != NULL)
        {
            if (pnode->random != NULL)
            {
                pnode->next->random = pnode->random->next;
            }
            pnode = pnode->next->next;
        }
    }

    void detachlist(RandomListNode *pHead)
    {
        RandomListNode *pnode = pHead;
        RandomListNode *tmp_node = pHead->next;
        while (tmp_node->next != NULL)//注意不能使用tmp_node直接判断，有问题
        {
            // tmp_node->next = tmp_node->next->next;
            pnode->next = tmp_node->next;
            tmp_node->next = pnode->next->next;
            tmp_node = tmp_node->next;    
            pnode = pnode->next;            
        }
        pnode->next =NULL;
        tmp_node->next =NULL;

    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
