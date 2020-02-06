#include <iostream>
#include <algorithm>
using namespace std;

int stringToInt(string num) {
	int n = 0;
	for(int i = 0; num[i]; i++) {
		n *= 10;
		n += num[i] - '0';
	}
	return n;
}

void intToString(int n, string & num) {
	num.resize(4, '0');
	for(int i = 3; i >= 0; i--) {
		num[i] = '0' + n % 10;
		n /= 10;
	}
}

int main() {
	string num;
	cin >> num;
	// 需要补0， 或者把字符串从字符串转整数再转回
	if(num.length() < 4)
		num.insert(0, 4 - num.length(), '0');
	int a = 0, b = 0;
	int c = -1;
	while(c != 6174 && c != 0) {
		// 把字符串从字符串转整数再转回
        // intToString(stringToInt(num), num);
		sort(num.begin(), num.end(), greater<int>());
		a = stringToInt(num);
		reverse(num.begin(), num.end());
		b = stringToInt(num);
		c = a - b;
		printf("%04d - %04d = %04d\n", a, b, c);
		intToString(c, num);
	}
	
}
