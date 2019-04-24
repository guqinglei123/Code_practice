#include<stdio.h>

int Eucild(int a,int b)
{
	if(a%b==0)
		return b;
	else
	{
		return Eucild(b,a%b);
	}
}

int fibonacci(int n)
{
	if (n==0||n==1)
		return 1;
	else
		return fibonacci(n-1)+fibonacci(n-2);
}
int main(void)
{
	int result;
	result=Eucild(100,40);
	printf("最大公约数=%d\n",result);
	result=fibonacci(10);
	printf("fibonacci=%d\n",result);
}