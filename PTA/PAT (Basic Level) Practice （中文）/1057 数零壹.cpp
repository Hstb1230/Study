#include <iostream>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	int len = s.length();
	int sum = 0;
	for(int i = 0; i < len; i++) {
		if(isalpha(s[i])) {
			sum += toupper(s[i]) - 'A' + 1;
		}
	}
//	cout << sum;
	int count[2] = {0};
	while(sum > 0) {
		count[sum % 2]++;
		sum /= 2;
	}
	printf("%d %d\n", count[0], count[1]);
}
