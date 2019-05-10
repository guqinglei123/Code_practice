#include <stdio.h>

/*自己写的答案*/
struct rational 
{
	int a,b;
};
//
int a1a2(struct rational z1, struct rational z2)
{
	return z1.a*z2.a;
}
int b1b2(struct rational z1, struct rational z2)
{
	return z1.b*z2.b;
}
int a1b2(struct rational z1, struct rational z2)
{
	return z1.a*z2.b;
}
int a2b1(struct rational z1, struct rational z2)
{
	return z1.b*z2.a;
}
int Eucild(int a, int b)
{
	if(a%b==0)
		return b;
	else
	{
		return Eucild(b, a%b);
	}
}
struct rational make_rational2(int a, int b)
{
	struct rational z;
	z.a = a;
	z.b = b;
	return z;
} 
//
struct rational add_complex(struct rational z1, struct rational z2)
{
	struct rational z;
	//	z1.a*z2.b+z2.a*z1.b
	//	z1.b*z2.b
	z.a=a1b2(z1,z2)+a2b1(z1,z2);
	z.b=b1b2(z1,z2);
	return z;
}
struct rational sub_complex(struct rational z1, struct rational z2)
{
	struct rational z;
	//z1.a*z2.b-z2.a*z1.b
	//z1.b*z2.b
	z.a=a1b2(z1,z2)-a2b1(z1,z2);
	z.b=b1b2(z1,z2);
	return z;
}
struct rational mul_complex(struct rational z1, struct rational z2)
{
	struct rational z;
	//	z1.a*z2.a
	//	z1.b*z2.b
	z.a=a1a2(z1,z2);
	z.b=b1b2(z1,z2);	
	return z;
}
struct rational div_complex(struct rational z1, struct rational z2)
{
	struct rational z;
	//	z1.a*z2.a
	//	z1.b*z2.b
	z.a=a1b2(z1,z2);
	z.b=a2b1(z1,z2);			
	return z;
}
struct rational print_rational2(struct rational z)
{
	if(z.a==z.b)
		printf("%d\n", 1);
	else if(z.a==0)
	{
		printf("%d\n", 0);
	}
	else if(z.a==-z.b)
	{
		printf("%d\n", -1);
	}
	else
	{
		int eucild=Eucild(z.a,z.b);
		z.a=z.a/eucild;
	     z.b=z.b/eucild;
		printf("%d/%d\n", z.a, z.b);
	}

}


/*参考答案*/

struct Ragtional 
{
	int numerator,denominator;
};
//
int GCD(int a, int b) 
{
	if(a%b == 0)
		return b;
	else
		return GCD(b, a%b);
}
struct Ragtional make_rational(int numerator, int denominator)
{
	struct Ragtional a;
	a.numerator = numerator;
	a.denominator = denominator;
	return a;
} 
//
struct Ragtional add_rational(struct Ragtional a, struct Ragtional b)//need to fix -
{
	struct Ragtional result;
	int max, gcm;
	max = GCD(a.denominator, b.denominator);
	gcm = (a.denominator*b.denominator) / max;
//	printf("gcm is %d\n", gcm);
	result.denominator = gcm;
	result.numerator = (a.numerator*gcm/a.denominator) + (b.numerator*gcm/b.denominator);
//	printf("numerator is %d\n", result.numerator);
	return result;
} 
struct Ragtional sub_rational(struct Ragtional a, struct Ragtional b)//need to fix -
{
	struct Ragtional result;
	int max, gcm;
	max = GCD(a.denominator, b.denominator);
	gcm = (a.denominator*b.denominator) / max;
//	printf("gcm is %d\n", gcm);
	result.denominator = gcm;
	result.numerator = (a.numerator*gcm/a.denominator) - (b.numerator*gcm/b.denominator);
//	printf("numerator is %d\n", result.numerator);
	return result;
}
struct Ragtional mul_rational(struct Ragtional a, struct Ragtional b)
{
	struct Ragtional result;
	result.numerator = a.numerator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	return result;
} 
struct Ragtional div_rational(struct Ragtional a, struct Ragtional b)
{
	struct Ragtional trans;
	trans.numerator = b.denominator;
	trans.denominator = b.numerator;
	return mul_rational(a, trans);
} 
void print_rational(struct Ragtional a)
{
	int max;
	max = GCD(a.numerator, a.denominator);
	if(a.denominator/max == 1)
	printf("%d\n", a.numerator/max);
	else
	printf("%d/%d\n", a.numerator/max, a.denominator/max);
}


int main(void)
{
	struct Ragtional a = make_rational(3, 10); /* a=1/8 */
	struct Ragtional b = make_rational(-2, 12); /* b=-1/8 */
	struct rational c = make_rational2(3, 10); /* a=1/8 */
	struct rational d = make_rational2(-2, 12); /* b=-1/8 */
	print_rational(add_rational(a, b));
	print_rational(sub_rational(a, b));
	print_rational(mul_rational(a, b));
	print_rational(div_rational(a, b));
	print_rational2(add_complex(c,d));
	print_rational2(sub_complex(c,d));
	print_rational2(mul_complex(c,d));
	print_rational2(div_complex(c,d));
	return 0;
}


