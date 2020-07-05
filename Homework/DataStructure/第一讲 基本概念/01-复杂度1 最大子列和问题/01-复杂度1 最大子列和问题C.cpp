#include <iostream>
using namespace std;

int main()
{
	int k;
	cin >> k;
	int a[k];
	for(int i = 0; i < k; i++)
		cin >> a[i];
	int tSum, mSum;
	tSum = mSum = 0;
	for(int i = 0; i < k; i++)
	{
		tSum += a[i];
		if(tSum > mSum)
			mSum = tSum;
		else if(tSum < 0)
			tSum = 0;
	}
	cout << mSum;
}
