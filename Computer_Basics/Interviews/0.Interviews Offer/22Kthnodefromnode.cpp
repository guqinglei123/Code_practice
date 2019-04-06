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
#include "mylist.h"
using namespace std;
class Solution
{
  public:
    ListNode *FindKthToTail(ListNode *pListHead, unsigned int k)
    {
        if (pListHead == NULL || k < 0)
            return NULL;
        ListNode *pre_listnode = pListHead;
        ListNode *tail_listnode = NULL;
        int step = 0;
        while (pre_listnode->next != NULL)
        {
            if (step > k)
            {
                pre_listnode = pre_listnode->next;
                tail_listnode = tail_listnode->next;
            }
            else if (step == k)//这里会忽略寻找的节点为首节点的情况
            {
                pre_listnode = pre_listnode->next;
                tail_listnode = pListHead->next;
            }
            else
            {
                pre_listnode = pre_listnode->next;
            }
            step++;
        }
        if ((pre_listnode->next == NULL) && ((step + 1) == k))//这寻找的节点为首节点的情况
            return pListHead;

        return (tail_listnode == NULL) ? NULL : tail_listnode->next;
    }
};

class Test_Solution
{
  public:
    Solution Sol;
    MyList mylist;
    void Test1()
    {
        printf("=====Test1 starts:=====\n");
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode2);
        mylist.ConnectListNodes(pNode2, pNode3);
        mylist.ConnectListNodes(pNode3, pNode4);
        mylist.ConnectListNodes(pNode4, pNode5);

        printf("expected result: 4.\n");
        ListNode *pNode = Sol.FindKthToTail(pNode1, 2);
        mylist.PrintListNode(pNode);

        mylist.DestroyList(pNode1);
    }

    // ²âÊÔÒªÕÒµÄ½áµãÊÇÁ´±íµÄÎ²½áµã
    void Test2()
    {
        printf("=====Test2 starts:=====\n");
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode2);
        mylist.ConnectListNodes(pNode2, pNode3);
        mylist.ConnectListNodes(pNode3, pNode4);
        mylist.ConnectListNodes(pNode4, pNode5);

        printf("expected result: 5.\n");
        ListNode *pNode = Sol.FindKthToTail(pNode1, 1);
        mylist.PrintListNode(pNode);

        mylist.DestroyList(pNode1);
    }

    // ²âÊÔÒªÕÒµÄ½áµãÊÇÁ´±íµÄÍ·½áµã
    void Test3()
    {
        printf("=====Test3 starts:=====\n");
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode2);
        mylist.ConnectListNodes(pNode2, pNode3);
        mylist.ConnectListNodes(pNode3, pNode4);
        mylist.ConnectListNodes(pNode4, pNode5);

        printf("expected result: 1.\n");
        ListNode *pNode = Sol.FindKthToTail(pNode1, 5);
        mylist.PrintListNode(pNode);

        mylist.DestroyList(pNode1);
    }

    // ²âÊÔ¿ÕÁ´±í
    void Test4()
    {
        printf("=====Test4 starts:=====\n");
        printf("expected result: nullptr.\n");
        ListNode *pNode = Sol.FindKthToTail(nullptr, 100);
        mylist.PrintListNode(pNode);
    }

    // ²âÊÔÊäÈëµÄµÚ¶þ¸ö²ÎÊý´óÓÚÁ´±íµÄ½áµã×ÜÊý
    void Test5()
    {
        printf("=====Test5 starts:=====\n");
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode2);
        mylist.ConnectListNodes(pNode2, pNode3);
        mylist.ConnectListNodes(pNode3, pNode4);
        mylist.ConnectListNodes(pNode4, pNode5);

        printf("expected result: nullptr.\n");
        ListNode *pNode = Sol.FindKthToTail(pNode1, 6);
        mylist.PrintListNode(pNode);

        mylist.DestroyList(pNode1);
    }

    // ²âÊÔÊäÈëµÄµÚ¶þ¸ö²ÎÊýÎª0
    void Test6()
    {
        printf("=====Test6 starts:=====\n");
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode2);
        mylist.ConnectListNodes(pNode2, pNode3);
        mylist.ConnectListNodes(pNode3, pNode4);
        mylist.ConnectListNodes(pNode4, pNode5);

        printf("expected result: nullptr.\n");
        ListNode *pNode = Sol.FindKthToTail(pNode1, 0);
        mylist.PrintListNode(pNode);

        mylist.DestroyList(pNode1);
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
