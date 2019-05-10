#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stack> 
using namespace std;
struct ListNode
{
    int val;
    struct ListNode *next;
    // ListNode(int x) : val(x), next(NULL)
    // {
    // }
};
class Solution {
public:
//方法一：通过stack来实现
    vector<int> printListFromTailToHead(ListNode* head) {
        ListNode* list_p=head;
        vector<int> vect;
        stack<int> sta;
        while(list_p!=NULL)
        {
            sta.push(list_p->val);
            list_p = list_p->next;
        }
        
        while(!sta.empty())
        {
            vect.push_back(sta.top());
            sta.pop();
        }

        return vect;
    }
//方法二：通过递归来实现
};
int main(int argc, char const *argv[])
{
    /* code */
    // {67,0,24,58}
    ListNode list[4];
    list[0].val = 67;
    list[0].next = &list[1];
    list[1].val = 0;
    list[1].next = &list[2];
    list[2].val = 24;
    list[2].next = &list[3];
    list[3].val = 58;
    list[3].next = NULL;

    Solution Sol;
    Sol.printListFromTailToHead(&list[0]);

    return 0;
}
