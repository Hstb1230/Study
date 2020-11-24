#include <iostream>
using namespace std;

int main()
{
	int k;
	cin >> k;
	int num[k];
	for(int i = 0; i < k; i++)
		cin >> num[i];
	int max = -1, mBeg = 0, mEnd = k - 1;
	int cur = 0, curBeg = 0;
	for(int i = 0; i < k; i++)
	{
		cur += num[i];
		if(cur < 0)
		{
			curBeg = i + 1;
			cur = 0;
		}
		else if(cur > max)
		{
			max = cur;
			mBeg = curBeg;
			mEnd = i;
		}
	}
	if(max == -1)
		max = 0;
	printf("%d %d %d", max, num[mBeg], num[mEnd]);
}
