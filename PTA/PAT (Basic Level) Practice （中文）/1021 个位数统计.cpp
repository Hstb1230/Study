#include <iostream>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	int c[10] = {0};
	for(int i = 0; s[i]; i++)
		c[s[i] - '0']++;
	for(int i = 0; i < 10; i++) {
		if(c[i])
			printf("%d:%d\n", i, c[i]);
	}
}
