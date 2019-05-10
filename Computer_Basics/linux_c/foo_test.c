#include<stdio.h>
 int foo(void)
 {
//	 int i;
//	 printf("%d\n",i);
//	 i=777;
	  int i=0;
	 {
	 	
	    int i=1;
	 	int j=2;
	    printf("i=%d,j=%d\n",i,j);
		
 	}
	 printf("i=%d\n",i);
 }

int main(void)
{

	foo();
	printf("hello\n");
	foo();
	return 0;
}