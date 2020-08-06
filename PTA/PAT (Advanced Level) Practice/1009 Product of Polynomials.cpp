#include <iostream>
using namespace std;

int main()
{
	double m[1001] = {0}, ans[2002] = {0};
	int n;
	int x; double a;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> a;
		m[x] += a;
	}
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> a;
		for(int j = 0; j < 1001; j++)
		{
			if(m[j] != 0)
				ans[x + j] += a * m[j];
		}
	}
	int cnt = 0;
	for(int i = 0; i < 2002; i++)
	{
		if(ans[i] != 0)
			cnt++;
	}
	cout << cnt;
	for(int i = 2001; i >= 0; i--)
	{
		if(ans[i] != 0)
			printf(" %d %.1f", i, ans[i]);
	}
}
