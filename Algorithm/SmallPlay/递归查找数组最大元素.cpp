/*
    Try to find the max element in array with "divide and conquer" instead of cycle.
*/
#include <iostream>
#include <vector>
using namespace std;

int max(vector<int> v)
{
	switch(v.size())
	{
		case 0:
			return 0;
		case 1:
			return v[0];
		case 2:
			return v[0] < v[1] ? v[1] : v[0];
	}
	vector<int> b(v.begin() + 1, v.end());
	int m = max(b);
	return v[0] < m ? m : v[0];
}

int main()
{
	vector<int> v(100);
	for(int i = 0; i < 100; i++)
		v[i] = i;
	printf("%d", max(v));
}
