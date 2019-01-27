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
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        if ((pHead1 == NULL) && (pHead2 == NULL))
            return NULL;
        else if (pHead1 == NULL)
            return pHead2;
        else if (pHead2 == NULL)
            return pHead1;
        ListNode *mergerlistnode = nullptr;
        ListNode *res_listnode = nullptr;
        if (pHead1->val > pHead2->val) //寰楀埌棣栬妭鐄1�7?
        {
            res_listnode = pHead2;
            mergerlistnode = res_listnode;
            pHead2 = pHead2->next;
        }
        else
        {
            res_listnode = pHead1;
            mergerlistnode = res_listnode;
            pHead1 = pHead1->next;
        }

        while (((pHead1 != NULL) ||(pHead2 != NULL)))//鍚堝苟杩炶��1�7
        {
            if ((pHead1 != NULL) && (pHead2 == NULL))
            {
                mergerlistnode->next = pHead1;
                break;
            }
            else if ((pHead1 == NULL) && (pHead2 != NULL))
            {
                mergerlistnode->next = pHead2;
                break;
            }
            else if (pHead1->val > pHead2->val)
            {
                mergerlistnode->next = pHead2;
                mergerlistnode = pHead2;
                pHead2 = pHead2->next;
            }
            else
            {
                mergerlistnode->next = pHead1;
                mergerlistnode = pHead1;
                pHead1 = pHead1->next;
            }
        }
        return res_listnode;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyList mylist;
    ListNode *Test(char *testName, ListNode *pHead1, ListNode *pHead2)
    {
        if (testName != nullptr)
            printf("%s begins:\n", testName);

        printf("The first list is:\n");
        mylist.PrintList(pHead1);

        printf("The second list is:\n");
        mylist.PrintList(pHead2);

        printf("The merged list is:\n");
        ListNode *pMergedHead = Sol.Merge(pHead1, pHead2);
        mylist.PrintList(pMergedHead);

        printf("\n\n");

        return pMergedHead;
    }

    // list1: 1->3->5
    // list2: 2->4->6
    void Test1()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode3);
        mylist.ConnectListNodes(pNode3, pNode5);

        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode6 = mylist.CreateListNode(6);

        mylist.ConnectListNodes(pNode2, pNode4);
        mylist.ConnectListNodes(pNode4, pNode6);

        ListNode *pMergedHead = Test("Test1", pNode1, pNode2);

        mylist.DestroyList(pMergedHead);
    }

    // 脕陆赂枚脕麓卤铆脰脨脫脨脰脴赂麓碌脛脢媒脳脰
    // list1: 1->3->5
    // list2: 1->3->5
    void Test2()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode3);
        mylist.ConnectListNodes(pNode3, pNode5);

        ListNode *pNode2 = mylist.CreateListNode(1);
        ListNode *pNode4 = mylist.CreateListNode(3);
        ListNode *pNode6 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode2, pNode4);
        mylist.ConnectListNodes(pNode4, pNode6);

        ListNode *pMergedHead = Test("Test2", pNode1, pNode2);

        mylist.DestroyList(pMergedHead);
    }

    // 脕陆赂枚脕麓卤铆露录脰禄脫脨脪禄赂枚脢媒脳脰
    // list1: 1
    // list2: 2
    void Test3()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);

        ListNode *pMergedHead = Test("Test3", pNode1, pNode2);

        mylist.DestroyList(pMergedHead);
    }

    // 脪禄赂枚脕麓卤铆脦陋驴脮脕麓卤铆
    // list1: 1->3->5
    // list2: 驴脮脕麓卤铆
    void Test4()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode3);
        mylist.ConnectListNodes(pNode3, pNode5);

        ListNode *pMergedHead = Test("Test4", pNode1, nullptr);

        mylist.DestroyList(pMergedHead);
    }

    // 脕陆赂枚脕麓卤铆露录脦陋驴脮脕麓卤铆
    // list1: 驴脮脕麓卤铆
    // list2: 驴脮脕麓卤铆
    void Test5()
    {
        ListNode *pMergedHead = Test("Test5", nullptr, nullptr);
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