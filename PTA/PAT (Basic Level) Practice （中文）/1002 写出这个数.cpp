#include <iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	int sum = 0;
	for(int i = 0; i < s.length(); i++) {
		sum += s[i] - '0';
	}
	// ������ת
	int copy_sum = sum;
	// ��λΪ0ʱ�޷����, �����Ҫ�������һλ
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
