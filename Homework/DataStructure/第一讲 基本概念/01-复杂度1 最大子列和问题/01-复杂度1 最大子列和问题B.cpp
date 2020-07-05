#include <iostream>
#include <algorithm>
using namespace std;

int d(int a[], const int & beg, const int & end)
{
	if(beg == end)
		return a[beg];
	// 求出中间最大序列和
	int tSum = 0, mSum = 0;
	for(int i = end / 2; i >= beg; i--)
	{
		tSum += a[i];
		if(tSum > mSum)
			mSum = tSum;
	}
	tSum = mSum;
	for(int i = end / 2 + 1; i <= end; i++)
	{
		tSum += a[i];
		if(tSum > mSum)
			mSum = tSum;
	}
	tSum = mSum;
	mSum = max(d(a, beg, (beg + end) / 2), d(a, (beg + end) / 2 + 1, end));
//	printf("%d %d : %d %d \n --- \n", beg, end, tSum, max(mSum, tSum));
	return max(mSum, tSum);
}

int main()
{
	int k;
	cin >> k;
	int a[k];
	for(int i = 0; i < k; i++)
		cin >> a[i];
	cout << d(a, 0, k - 1);
}
