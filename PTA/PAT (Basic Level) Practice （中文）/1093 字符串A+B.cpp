#include <iostream>
using namespace std;

int main()
{
	char hash[255] = {0};
	string s1, s2, s;
	getline(cin, s1);
	getline(cin, s2);
	s = s1 + s2;
	int len = s.length();
	for(int i = 0; i < len; i++)
	{
		if(hash[s[i]] == 0) putchar(s[i]);
		hash[s[i]] = 1;
	}
}
