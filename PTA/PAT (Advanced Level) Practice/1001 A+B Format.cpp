#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	int c = a + b;
	int num[10] = {1}, t = 0;
	if(c < 0)
	{
		cout << '-';
		c *= -1;
	}
	do
	{
		num[t++] = c % 1000;
		c /= 1000;
	} while(c != 0);
	for(int i = 0; i < t; i++)
	{
		if(i > 0)
			printf(",%03d", num[t - 1 - i]);
		else
			printf("%d", num[t - 1]);
	}
}
