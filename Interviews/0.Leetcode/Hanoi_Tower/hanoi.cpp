/*****************************************************************************************************
 * 汉诺塔问题：古代有一个梵塔，塔内有三个座A、B、C，A座上有64个盘子，盘子大小不等，
 * 大的在下，小的在上。有一个和尚想把这64个盘子从A座移到B座，但每次只能允许移动一个盘子，
 * 并且在移动过程中，3个座上的盘子始终保持大盘在下，小盘在上。
 * 参考网址：https://blog.csdn.net/woshinannan741/article/details/52815187
 * 扩展问题：给定一个整型数组arr,其中含有1、2和3，代表所有圆盘的目前状态，1代表 左柱，2代表中间柱子，
 * 3代表右柱子,arr[i]的值表示i+1个圆盘的位置。比如，arr={3,3,2,1},代表的是第一个圆盘在右柱子上，
 * 第二个圆盘在右柱子上，第三个圆盘在中间的柱子上，第四个柱子在左柱上。如果arr代表的状态时最优移动轨
 * 迹中出现的状态，要求返回arr这种状态是最优移动轨迹中的第几个状态。如果arr代表的不是最优一定状态，
 * 那么返回-1
    举个例子： 
    - arr=[1,1]。表示两个圆盘都在左边的柱子上面也就是初始状态，这个状态返回0 
    - arr=[2,1]。表示第一个圆盘在中间的柱子上，第二个圆盘在左边的柱子上，这种情况是两个圆盘的hanoi塔游戏中最优移动轨迹的第一步，所以返回值为1 
    - arr=[3,3]。俩个圆盘都在右边的柱子上，这种情况是两个圆盘的hanoi塔游戏中最优移动轨迹的最后一步，返回值为3 
    - arr=[2,2]。两个圆盘都在中间的柱子上面，在最优的转移状态中不会这种情况，所以返回-1
 * https://blog.csdn.net/woshinannan741/article/details/52818614
 * *******************************************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MX= 65;
int ans[MX];
void hanoi(int n,char A,char B,char C)
{
    if(n<=1) {
        printf("1 move %c to %c\n",A,C);
        return ;
    }
    hanoi(n-1,A,C,B);
    printf("%d move %c to %c \n",n,A,C);
    hanoi(n-1,B,A,C);
}

int step(int i,int from,int mid,int to)
{
    if(i==-1)return 0;
    if(ans[i]==mid) return -1;
    if(ans[i]==from) return step(i-1,from,to,mid);
    else {
        int res = step(i-1,mid,from,to);
        if(res==-1) return -1;
        return (1<<i)+res;
    }
}

int step2(int i)
{
    int from=1,mid=2,to=3;
    int res =0;
    while((i--)>=0) {
        if(ans[i]==mid) {
            return -1;
        }
        if(ans[i]==to) {
             res+=(1<<i);
             swap(mid,from);
        }else swap(mid,to);
    }
    return res;
}

int main(void)
{
    int  N;
    cin>>N;
    hanoi(N,'A','B','C');
    for(int i=0;i<N;i++) 
    {
        cin>>ans[i];
    }
    cout<<step(N-1,1,2,3)<<endl;
    cout<<step2(N-1)<<endl;   
    system("pause");  
}