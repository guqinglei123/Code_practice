#include <vector>
#include <list>
#include <set>
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
#include <functional>
#include <exception>
using namespace std;
//链表节点的定义
typedef struct Node {
    int data;
    struct Node *pNext;
} NODE, *PNODE;


PNODE *findNode(PNODE *head1, PNODE ×head2) {

    if (head1 == NULL || head2 == NULL) {
        //如果链表为空则很定不相交
        return NULL;
    }
    PNODE *p1, *p2;
    p1 = head1;
    p2 = head2;
    int len1 = 0; //第一个链表的长度
    int len2 = 0; //第二个链表的长度
    int diff = 0;
    while (NULL != p1->pNext) {
        p1 = p1->pNext;
        len1++;
    }
    while (NULL != p2->pNext) {
        p2 = p2->pNext;
        len2++;
    }
    if (p1 != p2) {
        //如果最后一个节点不相同则返回NULL
        return NULL;
    }
    diff = abs(len1 - len2);
    if (len1 > len2) {
        p1 = head1;
        p2 = head2;
    } else {
        p1 = head2;
        p2 = head1;
    }
    for (int i = 0; i < diff; i++) {
        p1 = p1->pNext;
    }
    while (p1 != p2) {
        p1 = p1->pNext;
        p2 = p2->pNext;
    }
    return p1;
}

int main(int argc, char const *argv[])
{

}
