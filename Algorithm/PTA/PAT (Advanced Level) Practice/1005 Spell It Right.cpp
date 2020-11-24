#include <iostream>
#include <vector>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int sum = 0;
	size_t len = s.length();
	for(size_t i = 0; i < len; i++)
		sum += (s[i] - '0');
	vector<int> n;
	do
	{
		n.push_back(sum % 10);
		sum /= 10;
	} while(sum != 0);
	string v[] = {
		"zero", "one", "two", "three", "four",
		"five", "six", "seven", "eight", "nine"};
	for(int i = n.size() - 1; i >= 0; i--)
	{
		cout << v[n[i]];
		if(i > 0)
			cout << " ";
	}
}
