#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	string s;
	for(int i = 0; i <= n; i++)
	{
		getline(cin, s);
		if(s == "") continue;
		printf("%d", int(s[s.find('T') - 2] - 'A' + 1));
	}
}
