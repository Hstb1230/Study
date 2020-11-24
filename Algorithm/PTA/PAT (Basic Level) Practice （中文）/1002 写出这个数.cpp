#include <iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	int sum = 0;
	for(int i = 0; i < s.length(); i++) {
		sum += s[i] - '0';
	}
	// 将数反转
	int copy_sum = sum;
	// 个位为0时无法表达, 因此需要额外填充一位
	sum = 1;
	do {
		sum *= 10;
		sum += copy_sum % 10;
		copy_sum /= 10;
	} while(copy_sum > 0);
	cout << sum << endl;
	const string num[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
	while(true) {
		cout << num[sum % 10];
		sum /= 10;
		if(sum == 1) break;
		else cout << " ";
	}
}
