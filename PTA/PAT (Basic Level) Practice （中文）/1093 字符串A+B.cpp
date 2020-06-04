#include <iostream>
#include <map>
using namespace std;

int main()
{
	map<char, bool> m;
	string s;
	for(int k = 0; k < 2; k++)
	{
		getline(cin, s);
		int len = s.length();
		for(int i = 0; i < len; i++)
		{
			if(m.count(s[i]) > 0)
				continue;
			putchar(s[i]);
			m[s[i]] = true;
		}
	}
}
