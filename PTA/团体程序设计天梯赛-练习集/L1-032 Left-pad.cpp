#include <iostream>
using namespace std;

int main() {
	int n;
	char c;
	cin >> n >> c;
	string s;
	getline(cin, s);
	getline(cin, s);
	int len = s.length();
	if(len >= n) {
		cout << s.substr(len - n, n);
	} else {
		for(int i = n - len; i > 0; i--)
			cout << c;
		cout << s;
	}
}
