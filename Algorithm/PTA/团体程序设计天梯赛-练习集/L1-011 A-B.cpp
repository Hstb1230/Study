#include <iostream>
using namespace std;

int main() {
	string a, b, s = "";
	// duda
	getline(cin, a);
	getline(cin, b);
	// cout << a << endl;
	// cout << b << endl;
	for(int i = 0; a[i] != '\0'; i++) {
		// if(b.find(a[i]) != b.npos) continue;
		for(int j = 0; b[j] != '\0'; j++) {
			if(b[j] == a[i]) break;
			if(b[j + 1] == '\0') {
				s.append(1, a[i]);
			}
		}
		
	}
	cout << s << endl;
}
