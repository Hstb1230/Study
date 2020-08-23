#include <iostream>
#include <algorithm>
using namespace std;

long long toDec(string s, long long radix)
{
	long long n = 0;
	for(auto c : s)
		n = n * radix + (isdigit(c) ? (c - '0') : (c - 'a' + 10));
	return n;
}

long long searchRadix(string a, long long b)
{
	char it = *max_element(a.begin(), a.end());
	long long low = (isdigit(it) ? (it - '0') : (it - 'a')) + 1;
	long long high = max(low, b);
	while(low <= high)
	{
		long long mid = (low + high) / 2;
		long long t = toDec(a, mid);
		if(t < -1 || t > b)
			high = mid - 1;
		else if(t == b)
			return mid;
		else
			low = mid + 1;
	}
	return 0;
}

int main()
{
	string a, b;
	int tag, radix;
	cin >> a >> b >> tag >> radix;
	long long n = toDec((tag == 1 ? a : b), radix);
	radix = searchRadix((tag == 1 ? b : a), n);
	if(radix > 0)
		cout << radix;
	else
		cout << "Impossible";
}
