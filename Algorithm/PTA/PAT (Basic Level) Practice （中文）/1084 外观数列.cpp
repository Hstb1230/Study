#include <iostream>
using namespace std;

string s(int d, int n)
{
	if(n == 1)
	{
		char str[2] = {'0' + d, 0};
		return str;
	}
	string str = s(d, n - 1);
	string g = "";
	int len = str.length();
	char c = str[0];
	int t = 0;
	for(int i = 1; i <= len; i++)
	{
		if(str[i] == c)
			continue;
		g.push_back(c);
		g.push_back('0' + (i - t));
		c = str[i];
		t = i;
	}
	return g;
}

int main()
{
	int d, n;
	cin >> d >> n;
	cout << s(d, n);
}
