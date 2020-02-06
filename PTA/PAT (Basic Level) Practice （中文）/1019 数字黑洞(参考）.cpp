#include <iostream>
#include <algorithm>
using namespace std;
bool cmp(char a, char b) {return a > b;}

int stoi(string num) {
	int n = 0;
	for(int i = 0; num[i]; i++) {
		n *= 10;
		n += num[i] - '0';
	}
	return n;
}

string to_string(int n) {
	string num;
	num.resize(4, '0');
	for(int i = 3; i >= 0; i--) {
		num[i] = '0' + n % 10;
		n /= 10;
	}
}

int main() {
	string s;
	cin >> s;
	s.insert(0, 4 - s.length(), '0');
	do {
		string a = s, b = s;
		sort(a.begin(), a.end(), cmp);
		sort(b.begin(), b.end());
		int result = stoi(a) - stoi(b);
		s = to_string(result);
		s.insert(0, 4 - s.length(), '0');
		cout << a << " - " << b << " = " << s << endl;
	} while (s != "6174" && s != "0000");
	return 0;
}
