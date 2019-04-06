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
int fun(int x, int y)
{
    static int m = 0;
    m = x + y + m;
    return m;
}

struct mtk1
{
    /* data */
    char i;
    int j;
    short k;
};

struct mtk2
{
    /* data */
    char i;
    short k;
    int j;
};

struct mtk3
{
    /* data */
    int j;
    char i;
    short k;
};

main(int argc, char const *argv[])
{
    /* code */
    //1
    char tmp[] = "Hello!";
    cout << tmp[strlen(tmp)] << endl; //''
    //2
    char tmp2[10];
    cout << strlen(tmp2) << endl; //0
    //3
    int i = 1, j = 2, k;
    k = fun(i, j);
    cout << k << "  "; //3
    k = fun(i, j);
    cout << k << endl; //6
    //4
    char *s, c, a[] = {1, 3, 5};
    //   c=*s;  有问题
    s = a;
    c = a[1];
    int len = strlen(a);
    cout << endl;
    //5
    cout << sizeof(mtk1) << "  " << sizeof(mtk2) << "  " << sizeof(mtk3) << endl; //12 8 8

    //6
    char str[] = {"Hello World"};
    cout << endl;
    //7如何将最后两位设为01b
    cout << endl;
    //8
    cout << endl;
    //9
    int x = 3, y = 4;
    x ^= y;
    y ^= x;
    x ^= y;
    cout << x << "  " << y << endl; //4  3
    //10
    cout << (0xdead << 0x10 + 0xbeef) << endl; //？？？0xdead<<0x10  应该为0xdead0000
    //13
    // for (int i = 0; i < 3; i++)
    // {
    //     pid_t fpid = fork();
    //     if (fpid == 0)
    //         printf("son/n");
    //     else
    //         printf("father/n");
    // }

    return 0;
}
