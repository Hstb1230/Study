#include <iostream>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	int a = 0, b = 0;
	bool seg = false;
	for(int i = 0; s[i] != '\0'; i++) {
		if(s[i] == ' ') {
			seg = true;
			continue;
		}
		if(!seg && a >= 0) {
			if(!(s[i] >= '0' && s[i] <= '9')) {
				a = -1;
				continue;
			} else {
				a *= 10;
				a += s[i] - '0';
			}
		} else if(seg && b >= 0) {
			if(!(s[i] >= '0' && s[i] <= '9')) {
				b = -1;
				continue;
			} else {
				b *= 10;
				b += s[i] - '0';
			}
		}
	}
	// cout << a << ' ' << b;
	if(a > 0 && a < 1001) cout << a;
	else cout << '?';
	cout << " + ";
	if(b > 0 && b < 1001) cout << b;
	else cout << '?';
	cout << " = ";
	if(a > 0 && a < 1001 && b > 0 && b < 1001) cout << a + b;
	else cout << '?';
}
