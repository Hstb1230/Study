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
		tSum = 0;
		for(int j = i; j < k; j++)
		{
			tSum += a[j];
			if(tSum > mSum)
				mSum = tSum;
		}
	}
	cout << mSum;
}
