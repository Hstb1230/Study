#include <iostream>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;

int main()
{
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	int min = min(min(a, b), c);
	// cout << min << endl;
	int count = 0;
	for(int i = 1; i <= n; )
	{
		if((i % a != 0) && (i % b != 0) && (i % c != 0))
		{
			// cout << i << ' ';
			count++;
			i += min;
		}
		else
		{
			i++;
		}
	}
	cout << count;
}
