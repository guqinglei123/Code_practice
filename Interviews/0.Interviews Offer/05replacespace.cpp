#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
using namespace std;
class Solution {
public:
    //情况一，该方法需要保证有额外的内存空间。
	void replaceSpace(char *str,int length) {
        if(length <=0)
            return;
        vector<char> str_vect;
        int i=0;
        while(str[i]!='\0')
        {
            if(str[i]==' ')
            {
                str_vect.push_back('%');
                str_vect.push_back('2');
                str_vect.push_back('0');
            }
            else
            {
                str_vect.push_back(str[i]);
            }
            i++;                
        }
        int kk= str_vect.size();
        if(length < str_vect.size()-1)
            return;
        str[str_vect.size()]='\0';
        for(int j = str_vect.size()-1;j>=0;j--)
        {
            str[j]=str_vect[j];
        }

	}
    //情况二，没有额外的空间
    //方法一，直接两个循环。一个循环查找空格，遇到空格则在通过一个循环将后面的数组都向后移动相应位数。
    //方法二，先计算空格的个数。通过双指针的方式实现(重点)。
};
int main(int argc, char const *argv[])
{
    /* code */
    // char aa[30]="We Are Happy";
    char aa[30]=" helloworld";
    Solution Sol;
    Sol.replaceSpace(aa,30);
    return 0;
}