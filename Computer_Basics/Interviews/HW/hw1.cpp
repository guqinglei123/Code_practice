#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    int number=0;
    double price=0.00;
    
    cin>>number>>price;

    int m1,m2;

    m1=m2=number*price;

    if(number>=3)
        m1=m1*0.7;

    m2-=2*(m2/10);

    if(m1>=50)
        m1-=10;

    if(m2>=99)
        m2-=6;

    m1 += 10;
    m2 += 6;

    int m1_=m1*100;
    int m2_=m2*100;

    if(m1==m2)
        cout<<0<<endl;
    else if(m1<m2)
        cout<<1<<endl;
    else
        cout<<2<<endl;

    return 0;
}