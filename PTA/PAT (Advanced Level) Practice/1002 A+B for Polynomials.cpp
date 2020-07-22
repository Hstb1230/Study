#include <iostream>
using namespace std;

int main()
{
	double m[1001] = {0};
	int k;
	int a;
	double b;
	for(int g = 0; g < 2; g++)
	{
		cin >> k;
		for(int i = 0; i < k; i++)
		{
			cin >> a >> b;
			m[a] += b;
		}
	}
	k = 0;
	for(int i = 0; i <= 1000; i++)
	{
		if(m[i] != 0.0) k++;
	}
	cout << k;
	for(int i = 1000; i >= 0; i--)
	{
		if(m[i] != 0.0)
			printf(" %d %.1f", i, m[i]);
	}
}
