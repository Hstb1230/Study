#include <iostream>
using namespace std;

int main()
{
	int m, k, n, t;
	cin >> m;
	while(m--)
	{
		cin >> k;
		if(k > 100)
			t = 1000;
		else if(k > 10)
			t = 100;
		else
			t = 10;
		bool isFind = false;
		for(int n = 1; n < 10; n++)
		{
//			printf("%d %d %d\n", t, n, n * k * k);
			if((n * k * k) % t == k)
			{
				printf("%d %d\n", n, n * k * k);
				isFind = true;
				break;
			}
		}
		if(!isFind)
			printf("No\n");
	}
}
