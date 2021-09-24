#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	int c = a + b;
	if(c < 0)
	{
		cout << '-';
		c *= -1;
	}
	
	int f[10] = { c % 1000 }, t = 1;
	while(c /= 1000)
		f[t++] = c % 1000;
		
	for(int i = 0; i < t; i++)
		printf(i ? ",%03d" : "%d", f[t - 1 - i]);
}
