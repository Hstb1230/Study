/*
    Try to calculate the sum of array element with "divide and conquer" instead of cycle.
*/
#include <iostream>
#include <vector>
using namespace std;

int sum(vector<int> a)
{
	if(a.size() < 2)
		return a[0];
	vector<int> b(a.begin() + 1, a.end());
	return a[0] + sum(b);
}

int main()
{
	vector<int> a(100);
	for(int i = 0; i < 100; i++)
	{
		a[i] = i + 1;
	}
	printf("%d", sum(a));
}
