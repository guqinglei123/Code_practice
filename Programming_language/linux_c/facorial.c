#include<stdio.h>
int factorial(int n)
{
	if(n==0)
		return 1;
	else
	{
		int recurse =factorial(n-1);
		int result = n*recurse;
		return result;
	}
}

int factorial_2(int n)
{

    int result = 1;
	while(n>0)
	{
		result =result *n;
		n=n-1;
	}
	return result;
	
}

int main(void)
{
	int result;
	result =factorial(25);
	printf("%d\n",result);
	result =factorial_2(25);
	printf("%d\n",result);
	return 0;
}