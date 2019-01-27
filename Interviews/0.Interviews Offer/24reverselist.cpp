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
    ListNode *ReverseList(ListNode *pHead)
    {
        if (pHead == NULL)
            return NULL;
        // if(pHead->next ==NULL)
        //     return pHead;
        ListNode *cur_listnode = pHead;
        ListNode *pre_listnode = NULL;
        ListNode *nex_listnode = pHead;
        /*        while(nex_listnode ->next != NULL)
        {
            cur_listnode = nex_listnode;
            nex_listnode = nex_listnode ->next; 
            cur_listnode ->next = pre_listnode;
            pre_listnode = cur_listnode;            
        }
        nex_listnode ->next = pre_listnode;*/
        while (cur_listnode->next != NULL)
        {                        
            nex_listnode = cur_listnode->next;
            cur_listnode->next = pre_listnode;
            pre_listnode = cur_listnode;
            cur_listnode = nex_listnode;
        }
        cur_listnode->next = pre_listnode;
        return cur_listnode;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyList mylist;
    ListNode *Test(ListNode *pHead)
    {
        printf("The original list is: \n");
        mylist.PrintList(pHead);

        ListNode *pReversedHead = Sol.ReverseList(pHead);

        printf("The reversed list is: \n");
        mylist.PrintList(pReversedHead);

        return pReversedHead;
    }

    // ÊäÈëµÄÁ´±íÓÐ¶à¸ö½áµã
    void Test1()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);
        ListNode *pNode2 = mylist.CreateListNode(2);
        ListNode *pNode3 = mylist.CreateListNode(3);
        ListNode *pNode4 = mylist.CreateListNode(4);
        ListNode *pNode5 = mylist.CreateListNode(5);

        mylist.ConnectListNodes(pNode1, pNode2);
        mylist.ConnectListNodes(pNode2, pNode3);
        mylist.ConnectListNodes(pNode3, pNode4);
        mylist.ConnectListNodes(pNode4, pNode5);

        ListNode *pReversedHead = Test(pNode1);

        mylist.DestroyList(pReversedHead);
    }

    // ÊäÈëµÄÁ´±íÖ»ÓÐÒ»¸ö½áµã
    void Test2()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);

        ListNode *pReversedHead = Test(pNode1);

        mylist.DestroyList(pReversedHead);
    }

    // ÊäÈë¿ÕÁ´±í
    void Test3()
    {
        Test(nullptr);
    }
};
int main(int argc, char *argv[])
{
    Test_Solution test;
    test.Test1();
    test.Test2();
    test.Test3();

    return 0;
}