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
#include "mylist.h"
using namespace std;

// struct ListNode
// {
//     int val;
//     struct ListNode *next;
//     ListNode(int x) : val(x), next(NULL)
//     {
//     }
// };

class Solution
{
  public:
    ListNode *deleteDuplication(ListNode *pHead) //这个入口函数不是特别恰当，因为也存在list就被修改的可能性
    {
        if (pHead == NULL)
            return NULL;
        ListNode *list_p = pHead;
        ListNode *pre_list_p = NULL;
        ListNode *res_list = new ListNode(0);
        res_list = NULL;
        while ((list_p!=NULL)&&(list_p->next != NULL))//注意到当只有最后一个和前面的不一样时，会使list_p==null
        {

            if (list_p->val != (list_p->next)->val)
            {
                pre_list_p = list_p;
                list_p = list_p->next;
            }
            else
            {
                while (list_p->val == (list_p->next)->val)
                {
                    list_p = list_p->next;
                    if (list_p->next == NULL)//注意最后几个数字相同的情况
                        break;
                }
                if (pre_list_p != NULL)
                    pre_list_p->next = (list_p->next);//如果前面存在不同的数据，则更新上一个不同node针向的位置
                else
                    res_list = (list_p->next);//如果前面都相同。则这个是返回的第一个不重复的值即列表头
                list_p = list_p->next;
            }
        }

        return (pHead->next != NULL) ? ((pHead->val != (pHead->next)->val) ? pHead : res_list) : pHead;
    }
};

MyList mylist;
Solution Sol;

void Test(char *testName, ListNode **pHead, int *expectedValues, int expectedLength)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    int index = 0;
    ListNode *pNode = Sol.deleteDuplication(*pHead);
    while (pNode != nullptr && index < expectedLength)
    {
        if (pNode->val != expectedValues[index])
            break;

        pNode = pNode->next;
        index++;
    }

    if (pNode == nullptr && index == expectedLength)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}
void Test1()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(2);
    ListNode *pNode3 = mylist.CreateListNode(3);
    ListNode *pNode4 = mylist.CreateListNode(3);
    ListNode *pNode5 = mylist.CreateListNode(4);
    ListNode *pNode6 = mylist.CreateListNode(4);
    ListNode *pNode7 = mylist.CreateListNode(5);

    mylist.ConnectListNodes(pNode1, pNode2);
    mylist.ConnectListNodes(pNode2, pNode3);
    mylist.ConnectListNodes(pNode3, pNode4);
    mylist.ConnectListNodes(pNode4, pNode5);
    mylist.ConnectListNodes(pNode5, pNode6);
    mylist.ConnectListNodes(pNode6, pNode7);

    ListNode *pHead = pNode1;

    int expectedValues[] = { 1, 2, 5 };
    Test("Test1", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    mylist.DestroyList(pHead);
}
void Test2()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(2);
    ListNode *pNode3 = mylist.CreateListNode(3);
    ListNode *pNode4 = mylist.CreateListNode(4);
    ListNode *pNode5 = mylist.CreateListNode(5);
    ListNode *pNode6 = mylist.CreateListNode(6);
    ListNode *pNode7 = mylist.CreateListNode(7);

    mylist.ConnectListNodes(pNode1, pNode2);
    mylist.ConnectListNodes(pNode2, pNode3);
    mylist.ConnectListNodes(pNode3, pNode4);
    mylist.ConnectListNodes(pNode4, pNode5);
    mylist.ConnectListNodes(pNode5, pNode6);
    mylist.ConnectListNodes(pNode6, pNode7);

    ListNode *pHead = pNode1;

    int expectedValues[] = {1, 2, 3, 4, 5, 6, 7};
    Test("Test2", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    mylist.DestroyList(pHead);
}

// ³ýÁËÒ»¸ö½áµãÖ®ÍâÆäËûËùÓÐ½áµãµÄÖµ¶¼ÏàÍ¬
void Test3()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(1);
    ListNode *pNode3 = mylist.CreateListNode(1);
    ListNode *pNode4 = mylist.CreateListNode(1);
    ListNode *pNode5 = mylist.CreateListNode(1);
    ListNode *pNode6 = mylist.CreateListNode(1);
    ListNode *pNode7 = mylist.CreateListNode(2);

    mylist.ConnectListNodes(pNode1, pNode2);
    mylist.ConnectListNodes(pNode2, pNode3);
    mylist.ConnectListNodes(pNode3, pNode4);
    mylist.ConnectListNodes(pNode4, pNode5);
    mylist.ConnectListNodes(pNode5, pNode6);
    mylist.ConnectListNodes(pNode6, pNode7);

    ListNode *pHead = pNode1;

    int expectedValues[] = {2};
    Test("Test3", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    mylist.DestroyList(pHead);
}

// ËùÓÐ½áµãµÄÖµ¶¼ÏàÍ¬
void Test4()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(1);
    ListNode *pNode3 = mylist.CreateListNode(1);
    ListNode *pNode4 = mylist.CreateListNode(1);
    ListNode *pNode5 = mylist.CreateListNode(1);
    ListNode *pNode6 = mylist.CreateListNode(1);
    ListNode *pNode7 = mylist.CreateListNode(1);

    mylist.ConnectListNodes(pNode1, pNode2);
    mylist.ConnectListNodes(pNode2, pNode3);
    mylist.ConnectListNodes(pNode3, pNode4);
    mylist.ConnectListNodes(pNode4, pNode5);
    mylist.ConnectListNodes(pNode5, pNode6);
    mylist.ConnectListNodes(pNode6, pNode7);

    ListNode *pHead = pNode1;

    Test("Test4", &pHead, nullptr, 0);

    mylist.DestroyList(pHead);
}

// ËùÓÐ½áµã¶¼³É¶Ô³öÏÖ
void Test5()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(1);
    ListNode *pNode3 = mylist.CreateListNode(2);
    ListNode *pNode4 = mylist.CreateListNode(2);
    ListNode *pNode5 = mylist.CreateListNode(3);
    ListNode *pNode6 = mylist.CreateListNode(3);
    ListNode *pNode7 = mylist.CreateListNode(4);
    ListNode *pNode8 = mylist.CreateListNode(4);

    mylist.ConnectListNodes(pNode1, pNode2);
    mylist.ConnectListNodes(pNode2, pNode3);
    mylist.ConnectListNodes(pNode3, pNode4);
    mylist.ConnectListNodes(pNode4, pNode5);
    mylist.ConnectListNodes(pNode5, pNode6);
    mylist.ConnectListNodes(pNode6, pNode7);
    mylist.ConnectListNodes(pNode7, pNode8);

    ListNode *pHead = pNode1;

    Test("Test5", &pHead, nullptr, 0);

    mylist.DestroyList(pHead);
}

// ³ýÁËÁ½¸ö½áµãÖ®ÍâÆäËû½áµã¶¼³É¶Ô³öÏÖ
void Test6()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(1);
    ListNode *pNode3 = mylist.CreateListNode(2);
    ListNode *pNode4 = mylist.CreateListNode(3);
    ListNode *pNode5 = mylist.CreateListNode(3);
    ListNode *pNode6 = mylist.CreateListNode(4);
    ListNode *pNode7 = mylist.CreateListNode(5);
    ListNode *pNode8 = mylist.CreateListNode(5);

    mylist.ConnectListNodes(pNode1, pNode2);
    mylist.ConnectListNodes(pNode2, pNode3);
    mylist.ConnectListNodes(pNode3, pNode4);
    mylist.ConnectListNodes(pNode4, pNode5);
    mylist.ConnectListNodes(pNode5, pNode6);
    mylist.ConnectListNodes(pNode6, pNode7);
    mylist.ConnectListNodes(pNode7, pNode8);

    ListNode *pHead = pNode1;

    int expectedValues[] = {2, 4};
    Test("Test6", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    mylist.DestroyList(pHead);
}

// Á´±íÖÐÖ»ÓÐÁ½¸ö²»ÖØ¸´µÄ½áµã
void Test7()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(2);

    mylist.ConnectListNodes(pNode1, pNode2);

    ListNode *pHead = pNode1;

    int expectedValues[] = {1, 2};
    Test("Test7", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    mylist.DestroyList(pHead);
}

// ½áµãÖÐÖ»ÓÐÒ»¸ö½áµã
void Test8()
{
    ListNode *pNode1 = mylist.CreateListNode(1);

    mylist.ConnectListNodes(pNode1, nullptr);

    ListNode *pHead = pNode1;

    int expectedValues[] = {1};
    Test("Test8", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    mylist.DestroyList(pHead);
}

// ½áµãÖÐÖ»ÓÐÁ½¸öÖØ¸´µÄ½áµã
void Test9()
{
    ListNode *pNode1 = mylist.CreateListNode(1);
    ListNode *pNode2 = mylist.CreateListNode(1);

    mylist.ConnectListNodes(pNode1, pNode2);

    ListNode *pHead = pNode1;

    Test("Test9", &pHead, nullptr, 0);

    mylist.DestroyList(pHead);
}

// ¿ÕÁ´±í
void Test10()
{
    ListNode *pHead = nullptr;

    Test("Test10", &pHead, nullptr, 0);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();

    return 0;
}
