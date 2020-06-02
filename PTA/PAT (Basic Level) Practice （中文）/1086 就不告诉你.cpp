#include <iostream>
using namespace std;

int main()
{
	int a, b, c;
	cin >> a >> b;
	c = a * b;
	bool isZero = true;
	do
	{
		if(!(c % 10 == 0 && isZero))
		{
			isZero = false;
			cout << c % 10;
		}
		c /= 10;
	} while(c != 0);
}
