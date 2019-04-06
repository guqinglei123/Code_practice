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
 void reverse(char s[])
   {
       int c, i, j;
       for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
           c = s[i];
           s[i] = s[j];
           s[j] = c;
       }
   }
void itoa1(int input, char *output, int radix)
{
    int n = input;
    char* s=output;
    int  w = radix;
    int i, sign;
    void reverse(char s[]);
    sign = n;
    i =0;
    do{
        s[i++] = abs(n%10) + '0';
    }while((n/=10) != 0);
    if(sign <0)
        s[i++] = '-';
    while(i < w)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
    return;
}
main(int argc, char const *argv[])
{
    /* code */
    int input;
    char output[32];

    scanf("%x", &input);
    itoa1(input, output, 10);
    printf("%s\n", output);
    return 0;
}
