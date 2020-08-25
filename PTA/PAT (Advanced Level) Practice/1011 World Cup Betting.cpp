#include <iostream>
using namespace std;

int main()
{
	double bet[3][3];
	int m[3] = { 0 };
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		{
			cin >> bet[i][j];
			if(bet[i][j] > bet[i][m[i]])
				m[i] = j;
		}
	char r[] = "WTL";
	double best = 1;
	for(int i = 0; i < 3; i++)
	{
		printf("%c ", r[m[i]]);
		best *= bet[ i ][ m[i] ];
	}
	best = (best * 0.65 - 1) * 2;

	printf("%.2f", best);
}
