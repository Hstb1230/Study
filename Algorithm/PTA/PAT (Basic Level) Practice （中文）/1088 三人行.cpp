#include <iostream>
#include <cmath>
using namespace std;

void printPowerDiff(int m, double n)
{
	if(m == n)
		cout << " Ping";
	else if(m > n)
		cout << " Gai";
	else 
		cout << " Cong";
}

int main()
{
	int m, x, y;
	cin >> m >> x >> y;
	int a, b;
	double c;
	for(int i = 99; i >= 10; i--)
	{
		a = i;
		b = i % 10 * 10 + i / 10;
		c = abs(a - b) * 1.0 / x;
		if(b == c * y)
		{
	        cout << a;
			printPowerDiff(m, a);
			printPowerDiff(m, b);
			printPowerDiff(m, c);
			return 0;
		}
	}
    cout << "No Solution";
    return 0;
}
