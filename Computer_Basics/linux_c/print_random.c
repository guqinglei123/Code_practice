#include<stdio.h>
#include<stdlib.h>
#define N 20

int a[N];

void gen_random (int upper_bound)
{
	int i;
	for (i=0;i<N;i++)
		a[i]= rand()%upper_bound;
}

void print_random()
{
	int i;
	for(i=0;i<N;i++)
		printf("%d",a[i]);
	printf("\n");
}

int howmany(int value)
{
	int count =0,i;
	for (i=0;i<N;i++)
		if(a[i]==value)
			++count;
	return count;
	
}

int main(void)
{
	int i,j,sum,histogram[10]={};
	gen_random(10);
//	print_random();
	
//
//	for (i=0;i<10;i++)
//		printf("%d\t%d\n",i,howmany(i));

// 直方图的打印
	for (i=0;i<10;i++)
		histogram[i]=howmany(i);	
	
	for (i=0;i<10;i++)
		printf("%d\t",i);
	printf("\n",i);
	for (i=0;i<10;i++)
		printf("%d\t",histogram[i]);
    printf("\n",i);

	do{
			sum=0;
			for(i=0;i<=9;i++)
				sum +=histogram[i];
			for(j=0;j<=9;++j)
			{
				if(histogram[j]!=0)
				{
					printf("*");
					--histogram[j];
					printf("\t");
				}
				else
					printf("\t");
			}
			printf("\n");	
	}while(sum!=0);
	return 0;
}