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
using namespace std;
int pass, fail;
#define ASSERT_EQ(x, y) (y == x) ? pass++ : fail++;

struct CM
{
    char t : 4;
    char k : 4;
    unsigned short i : 8;
    unsigned long m;
    unsigned long array[0];
};
struct ls1
{
    char i;
    int p[0];
};

struct ls2
{
    char i;
    int p[1];
};
struct point
{
    int a;
    int *b;
} p;
int x = 0;
class kk1
{
    char i;
    int p[0];
    union bb {
        long gg;
        char vv;
    };
    int jj[20];
};

//计算英文单词数量
//只是统计了单词的数量，不保证单词的正确性,如果需要则需要匹配模板
//符号不单独计算

int count_word(char *buf)
{
    int res = 0;

    if ((buf == NULL) || (buf == " ") || (buf == "/0"))
        return 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        if (((buf[i] != ' ') && (buf[i + 1] == ' ')) || ((buf[i] != ' ') && (buf[i + 1] == '\0')))
        {
            int m = i;
            while ((m > 0) && (buf[m] != ' ')) //针对于测试情况2的处理
            {
                if ((buf[m] > 'A') && (buf[m] < 'z'))
                {
                    res++;
                    break;
                }
                else
                    m--;
            }
        }
    }
    return res;
}

//单元测试案例
void ut(void)
{
    static int assert_fail, assert_pass;
    pass = 0;
    fail = 0;
    //正确性检查
    ASSERT_EQ(count_word("hello word!"), 2);
    ASSERT_EQ(count_word("hello !!」!! word!"), 2);
    ASSERT_EQ(count_word("hello word!!!! word!"), 3);
    // //边界检查
    ASSERT_EQ(count_word(""), 0);
    ASSERT_EQ(count_word("/0"), 0);
    ASSERT_EQ(count_word(" "), 0);
    ASSERT_EQ(count_word(NULL), 0);
    ASSERT_EQ(count_word("!!!!"), 0);
    assert_pass = pass;
    assert_fail = fail;
    printf("Test Report :\n Fail:%d\n Pass :%d\n", assert_fail, assert_pass);
}

int main(int argc, char const *argv[])
{
    //     /* code */
    //     cout << sizeof(kk1) << endl;

    //     //8.
    //     p.a = 400;
    //     p.b = (int *)300;//0x258
    //     cout << (p.a + p.b) << endl;//??? 0x898
    //     //9.
    //     cout << sizeof(CM) << endl; //1+1+2(对齐)+4=8
    // //11
    // #include "a.c"
    //     cout << x << endl;//2

    //     //12
    //     int aa,bb=2,cc=3,dd=-20;
    //     unsigned int ee= 0x10;
    //     aa=(bb!=cc)&&(dd+ee<6);
    //     cout<<aa<<endl; //0

    //     //13
    //     int *p1,*p2;
    //     int value;
    //     p1 =(int *)0x500;
    //     p2=(int *)0x508;
    //     value = p2 -p1;
    //     cout<<value<<endl; //2
    //     //14

    //     //15

    //     //16
    //     // sprintf(buf + sprintf(buf,"%s","abc%d"),"%s","efg%%d");
    //     // printf(buf,300);

    //     //17
    //     // long (*b)[100];
    //     // cout<<(*b)<<endl;

    //     //19
    //     cout << sizeof(ls1) << "    "; //1+3(对齐)=4
    //     cout << sizeof(ls2) << endl; //1+3(对齐)+4=8
    //     //20
    //     int a=0,b=0,c=0,d=0,e=0;
    //     if(++a>0&&++b>0||++c>0&&++d>0)
    //         ++e;
    //     cout<<a+b+c+d+e<<endl;//1   1   0   0   1
    //21

    ut();
    return 0;
}
