#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;

	int g, p, l, t;
	g = p = l = t = 0;
	for(int i = 0; s[i] != '\0'; i++) {
		if(s[i] == 'G' || s[i] == 'g') g++;
		else if(s[i] == 'P' || s[i] == 'p') p++;
		else if(s[i] == 'L' || s[i] == 'l') l++;
		else if(s[i] == 'T' || s[i] == 't') t++;
	}
	while(g > 0 || p > 0 || l > 0 || t > 0) {
		if(g-- > 0) cout << 'G';
		if(p-- > 0) cout << 'P';
		if(l-- > 0) cout << 'L';
		if(t-- > 0) cout << 'T';
	}
}
