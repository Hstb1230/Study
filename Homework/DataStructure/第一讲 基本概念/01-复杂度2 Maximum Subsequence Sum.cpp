#include <iostream>
using namespace std;

int main()
{
	int k;
	cin >> k;
	int a[k];
	for(int i = 0; i < k; i++)
		cin >> a[i];
	int tSum = 0, mSum = -1;
	int tBeg = 0;
	int mBeg = 0, mEnd = k - 1;
	for(int i = 0; i < k; i++)
	{
		tSum += a[i];
		if(tSum < 0)
		{
			tSum = 0;
			tBeg = i + 1;
		}
		else if(tSum > mSum)
		{
			mSum = tSum;
			mBeg = tBeg;
			mEnd = i;
		}
	}
	if(mSum < 0)
		mSum = 0;
	printf("%d %d %d", mSum, a[mBeg], a[mEnd]);
}
