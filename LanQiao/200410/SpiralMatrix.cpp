#include <iostream>
using namespace std;

int main()
{
	int n, m, r, c;
	cin >> n >> m >> r >> c;
	r--, c--;
	int max_n = n - 1, max_m = m - 1;
	int min_n = 0, min_m = 0;
	int i = 0, j = 0;
	int t = 1; // 表示当前的数字
	while(i != r || j != c)
	{
		if(i < max_n && j < max_m)
		{
			// Right
			j++;
			if(j == max_m)
			{
				min_n++;
			}
		}
		else if(j == max_m && i < max_n)
		{
			// Down
			i++;
			if(i == max_n)
			{
				max_m--;
			}
		}
		else if(i == max_n && j > min_m)
		{
			// Left
			j--;
			if(j == min_m)
			{
				max_n--;
			}
		}
		else if(j == min_m && i > min_n)
		{
			// Up
			i--;
			if(i == min_n)
			{
				min_m++;
			}
		}
		t++;
//		cout << i << ' ' << j << endl;
	}
	cout << t;
}
