#include <iostream>
using namespace std;

int main()
{
	double bet[3][3];
	int m;
	double best = 1;
	char r[] = "WTL";
	for(int i = 0; i < 3; i++)
	{
		m = 0;
		for(int j = 0; j < 3; j++)
		{
			cin >> bet[i][j];
			if(bet[i][j] > bet[i][m])
				m = j;
		}
		printf("%c ", r[m]);
		best *= bet[i][m];
	}
	best = (best * 0.65 - 1) * 2;

	printf("%.2f", best);
}
