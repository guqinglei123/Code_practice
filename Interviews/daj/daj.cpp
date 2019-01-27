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
//知识点一：占用内存以及字节对齐
//1.1对齐字节宽度
struct CAT_s
{
    int ld;             //4字节
    char Color;         //1字节
    unsigned short Age; //2字节
                        //对齐，补一个字节
    char *Name;         //8字节
    void (*Jump)(void); //8字节
} Garfield;             //2014年，8字节对齐
struct CAT2_s
{
    char Color; //1字节
    int ld;     //4字节

} Garfield2; //4字节对齐（最大宽度为4）
struct CAT3_s
{
    unsigned short Age; //1字节
    char Color1;        //1字节
    char Color2;        //1字节
    char Color3;        //1字节

} Garfield3; //2字节对齐（最大宽度为2）

//1.2联合体
union B {
    char c;   //1字节
    int i;    //4字节
    double d; //8字节
} test_B;     //2018年B卷，取最大宽度

union C {
    int a[5];
    double c;
} test_C; //最大的变量宽度的整数倍

union D {
    int a[5];
    double c;
} __attribute__((packed)) test_D; //最大的变量宽度的整数倍

//1.3不对齐或者指定对齐位数
typedef int (*func_t)(int a, int b);
typedef struct foo
{
    func_t f;                    //8字节
    char a;                      //1字节
    char *b;                     //8字节
    int c;                       //4字节
} __attribute__((packed)) foo_t; //不对齐。注意attribute前后都是两个_,其含义为控制该结构不对齐

typedef struct foo2
{
    func_t f; //8字节
    char a;   //1字节
              //对齐，补7字节
    char *b;  //8字节
    int c;    //对齐，补4字节
} foo2_t;     //该结构8字节对齐.2018年B卷。
//注意在64位机器中，默认宽度最大超过8，如果超过按8计算；注意在32位机器中，默认宽度最大超过4,其原因为
//其原因为:对齐长度是在，#pragma pack指定的数值和这个数据成员自身长度中，选择比较小。
//pragma pack(n),在32位中默认为4,64中默认为8； 　　

//1.4 union和struct的结合(2018年B卷)
struct __attribute__((packed)) testStruct1
{
    char A; //1字节
    int B;  //4字节
    char C; //1字节
};

struct testStruct2
{
    union B {
        int A;       //4字节
        char c;      //1字节
    };               //不占空间
    unsigned char C; //1个字节
                     //补3个字节
    int D;           //4个字节
};

struct testStruct3
{
    union B {
        int A;       //4字节
        char c;      //1字节
    };               //不占空间
    unsigned char C; //1个字节
};

struct testStruct4
{
    union B {
        int A;  //4字节
        char c; //1字节
    };          //占1字节空间
};

union B1 {
    int A;  //4字节
    char c; //1字节
};

struct testStruct5
{

    B1 b;            //4个字节
    unsigned char C; //1个字节
                     //补3个字节
    int D;           //4个字节
};

union B2 {
    int a[5]; //20
    short b;  //2
    double c; //8
    char p2;  //1
};            //8字节对齐

struct testStruct6
{
    int n;      // 4字节
                // 补4字节
    B2 a;       // 24字节，但是8字节对齐
    char c[10]; // 10字节
                // 补6字节
};              //是8字节对齐

union B3 {
    int t;   //4
    short m; //2
    char p;  //1
};

struct testStruct7
{
    B3 a;     //4
              //补4字节
    double c; //8
    char p2;  //1
              //补7字节
};            //是8字节对齐

//1.4pragma pack对齐

//知识点二：大小端口对齐（2014年）
//大端字节(数据的高位，保存在内存的低地址中)
//小端模式(数据的高位，保存在内存的高地址中)
union endian {
    int a;
    short b;
} test_endian; //联合体union的存放顺序是所有成员都从低地址开始存放

static union {
    char c[4];
    unsigned long mylong;
} endian_test = {{'l', '?', '?', 'b'}};
#define ENDIANNESS ((char)endian_test.mylong)

//大小端口对齐
//知识点三：memset是按字节初始化的，fill则是按块初始化(2018年B卷)
//知识点四：const指针与数组名(2018年B卷)
//知识点五：二维数组(2018年B卷)
//知识点六：(2018年B卷)
int min(int x, int y, int &num_min)
{
    num_min++;
    return x < y ? x : y;
}
int max(int x, int y, int &num_max)
{
    num_max++;
    return x < y ? y : x;
}
int increment(int *x, int y, int &num_increment)
{
    num_increment++;
    return *x += y;
}
int square(int x, int &num_square)
{
    num_square++;
    return x * x;
}


int main(int argc, char const *argv[])
{
    //知识点一：占用内存以及字节对齐
    // printf('%d \n',sizeof(Garfield));
    cout << sizeof(Garfield) << endl;  //24个字节
    cout << sizeof(Garfield2) << endl; //8个字节
    cout << sizeof(Garfield3) << endl; //6个字节

    cout << sizeof(test_B) << endl; //8个字节
    cout << sizeof(test_C) << endl; //24个字节
    cout << sizeof(test_D) << endl; //20个字节

    cout << sizeof(foo_t) << endl;  //21个字节
    cout << sizeof(foo2_t) << endl; //32个字节

    cout << sizeof(struct testStruct1) << endl;                                //6
    cout << sizeof(struct testStruct2) << endl;                                //8
    cout << (sizeof(struct testStruct1) + sizeof(struct testStruct2)) << endl; //14
    cout << sizeof(struct testStruct3) << endl;                                //1
    cout << sizeof(struct testStruct4) << endl;                                //1
    cout << sizeof(struct testStruct5) << endl;                                //12
    cout << sizeof(struct testStruct6) << endl;                                //48
    cout << sizeof(struct testStruct7) << endl;                                //24

    //知识点二：大小端判断
    //方法一：
    int a = 1; //内存表示为0x00000001.
    char *p = (char *)&a;
    if (*p == 1)
        printf("small \n");
    else
        printf("big \n");
    //方法二：
    test_endian.a = 0x12345678;
    if (test_endian.b == 0x1234)
        printf("big \n");
    if (test_endian.b == 0x5678)
        printf("small \n");
    //方法三(linux内核的实现)：
    cout << ENDIANNESS << endl;

    //知识点三：memset是按字节初始化的，fill则是按块初始化
    uint32_t num1[50],num2[50];
    fill(num1, num1 + 50, 1);
    printf("%d\n", num1[10]); //1
    memset(num2, 1, 50 * sizeof(int));
    printf("%d\n", num2[10]); //16843009

    //知识点四：const指针与数组名
    char str1[] = "abc";
    char str2[] = "abc";

    const char str3[] = "abc";
    const char str4[] = "abc";

    const char *str5 = "abc";
    const char *str6 = "abc";

    char *str7 = "abc";
    char *str8 = "abc";

    cout << (str1 == str2) << endl; //0
    cout << (str3 == str4) << endl; //0
    cout << (str5 == str6) << endl; //1
    cout << (str7 == str8) << endl; //1

    //知识点五：二维数组
    int table[7][8];
    cout << (sizeof(table) / sizeof(table[0])) << endl;       //7   行数
    cout << (sizeof(table) / sizeof(table[0][0])) << endl;    //56  元素个数
    cout << (sizeof(table[0]) / sizeof(table[0][0])) << endl; //8  列数
    cout << (sizeof(table)) << endl;                          //224  总的字节数

    //知识点六：
    int num_min = 0, num_max = 0, num_square = 0, num_increment = 0;
    int x = 5, y = 50;
    int t;
    for (int i = min(x, y, num_min); i < max(x, y, num_max); increment(&i, 1, num_increment))
        t += square(i, num_square);
    cout << num_min << endl; //1
    cout << num_max << endl; //46
    cout << num_square << endl;//45
    cout << num_increment << endl;//45
    return 0;
}
