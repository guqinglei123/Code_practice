
//int data[10] = {0,1,2,3,4,5,6,7,8,9}将数组划分2组, 分别为A和B，要求B[i]都比A[i]大 有多少种可能性
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
typedef struct CM
{
    unsigned int t1 : 8;
    unsigned int t2 : 8;
    unsigned int t3 : 16;
    int cc[31];

} CM;
class A
{
  public:
    f() { cout << "A::F" << endl; }
    virtual g() { cout << "A::g" << endl; }
};
class B : public  A
{
  public:
    f() { cout << "B::F" << endl; }
    virtual g() { cout << "B::g" << endl; }
};
class B1
{
  public:
    virtual f1();
    virtual f2();
    virtual f3();
};
class B2
{
    virtual f1();
    virtual f2();
    virtual f3();
};
class B3
{
    virtual f1();
    virtual f2();
    virtual f3();
};
class B4 : public  B1,public  B2,public  B3
{
    virtual f4();
    virtual f5();
    char i;
    int p[0];
    union bb
    {
        long gg;
        char vv;
    };
    int jj[20];
};


    main(int argc, char const *argv[])
{
    /* code */
    cout << sizeof(CM) << endl;
    cout << sizeof(B4) << endl;
    unsigned
    return 0;
}