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
    ListNode *EntryNodeOfLoop(ListNode *pHead)
    {
        if (pHead == NULL)
            return NULL;
        ListNode *meetp =MeetingNode(pHead);
        if(meetp == NULL)
            return NULL;
        //计算节点数
        int node_nums = 1;
        ListNode *tempp = meetp->next;
        while(tempp != meetp)
        {
            tempp = tempp->next;
            node_nums++;
        }
        //双节点寻找入口
        int k = node_nums;
        ListNode *pre_listnode = pHead;
        ListNode *tail_listnode = NULL;
        int step = 0;
        while (pre_listnode!= tail_listnode)
        {
            if (step >= k)
            {
                pre_listnode = pre_listnode->next;
                tail_listnode = tail_listnode->next;
            }
            else if (step == k-1)
            {
                pre_listnode = pre_listnode->next;
                tail_listnode = pHead;
            }
            else
            {
                pre_listnode = pre_listnode->next;
            }
            step++;
        }
        return tail_listnode;
    }
    ListNode *MeetingNode(ListNode *pHead)
    {
       
        ListNode *slowp =pHead-> next;//注意一个问题，slowp的next是存在的主要phead不为NULL，但是下一个的下一个就不一定。下面同理
        if((pHead -> next) == NULL)//注意这个是只有一个节点且没有环的情况
            return NULL;
        ListNode *fastp =pHead-> next ->next;
        while((fastp != NULL)&&(slowp != NULL))
        {
            if(fastp == slowp)
                return fastp;
            slowp = slowp -> next;
            if((fastp -> next) == NULL)
                return NULL;//为什么不是return NULL？
            else
                fastp = fastp -> next ->next;
        }
        return NULL;
    }

    ListNode *EntryNodeOfLoop2(ListNode *pHead)//断链法.访问过的next都为NULL https://blog.csdn.net/gatieme/article/details/51602910
    {
        if (pHead == NULL)
            return NULL;
    }
};
class Test_Solution
{
  public:
    Solution Sol;
    MyList mylist;
    void Test(char *testName, ListNode *pHead, ListNode *entryNode)
    {
        if (testName != nullptr)
            printf("%s begins: ", testName);

        if (Sol.EntryNodeOfLoop(pHead) == entryNode)
            printf("Passed.\n");
        else
            printf("FAILED.\n");
    }

    // A list has a node, without a loop
    void Test1()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);

        Test("Test1", pNode1, nullptr);

        mylist.DestroyList(pNode1);
    }

    // A list has a node, with a loop
    void Test2()
    {
        ListNode *pNode1 = mylist.CreateListNode(1);
        mylist.ConnectListNodes(pNode1, pNode1);

        Test("Test2", pNode1, pNode1);

        delete pNode1;
        pNode1 = nullptr;
    }

    // A list has multiple nodes, with a loop
    void Test3()
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
        mylist.ConnectListNodes(pNode5, pNode3);

        Test("Test3", pNode1, pNode3);

        delete pNode1;
        pNode1 = nullptr;
        delete pNode2;
        pNode2 = nullptr;
        delete pNode3;
        pNode3 = nullptr;
        delete pNode4;
        pNode4 = nullptr;
        delete pNode5;
        pNode5 = nullptr;
    }

    // A list has multiple nodes, with a loop
    void Test4()
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
        mylist.ConnectListNodes(pNode5, pNode1);

        Test("Test4", pNode1, pNode1);

        delete pNode1;
        pNode1 = nullptr;
        delete pNode2;
        pNode2 = nullptr;
        delete pNode3;
        pNode3 = nullptr;
        delete pNode4;
        pNode4 = nullptr;
        delete pNode5;
        pNode5 = nullptr;
    }

    // A list has multiple nodes, with a loop
    void Test5()
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
        mylist.ConnectListNodes(pNode5, pNode5);

        Test("Test5", pNode1, pNode5);

        delete pNode1;
        pNode1 = nullptr;
        delete pNode2;
        pNode2 = nullptr;
        delete pNode3;
        pNode3 = nullptr;
        delete pNode4;
        pNode4 = nullptr;
        delete pNode5;
        pNode5 = nullptr;
    }

    // A list has multiple nodes, without a loop
    void Test6()
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

        Test("Test6", pNode1, nullptr);

        mylist.DestroyList(pNode1);
    }

    // Empty list
    void Test7()
    {
        Test("Test7", nullptr, nullptr);
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

    return 0;
}