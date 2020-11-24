#include <iostream>
using namespace std;

int main() {
	int l, n;
	cin >> l >> n;
	string s(l, 'z');
	n--;
	int i = s.length() - 1;
	while(n > 0) {
		s[i] -= n % 26;
		n /= 26;
		i--;
	}
	cout << s;
}
