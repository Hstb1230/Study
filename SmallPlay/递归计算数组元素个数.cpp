/*
    Try to calculate the array size with "divide and conquer" instead of cycle.
*/
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;

int count(vi v)
{
	if(v.size() < 2)
		return v.size();
	vi a(v.begin() + 1, v.end());
	return 1 + count(a);
}

int main()
{
	vi v(100);
	printf("%d", count(v));
}
