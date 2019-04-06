#include<string>
#include<iostream>
using std::cout;
using std::string;
using std::endl;
string s("Hello world!!");
int main(void)
{
	for (auto c : s)
	{
		c = toupper(c);
		cout << c <<endl;

	}
	cout << s << endl;
	auto it =s.begin();
//	cout << it << endl;
	cout << *it <<endl;
}
