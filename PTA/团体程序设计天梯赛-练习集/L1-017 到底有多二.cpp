#include <iostream>
using namespace std;

int main() {
	char s[51];
	cin >> s;
	double rate = 100;
	int len = 0;
	int count = 0;
	for(int i = 0; s[i] != '\0'; i++) {
		if(s[i] == '-') {
			rate *= 1.5;
			continue;
		}
		len++;
		if(s[i] == '2') count++;
		if(s[i + 1] == '\0' && (s[i] - '0') % 2 == 0) rate *= 2;
	}
	printf("%.2f%%", rate * count / len);
}
