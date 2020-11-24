#include <iostream>
using namespace std;

int main() {
	char sign;
	int first;
	char second[10000];
	int third = 0;
	scanf("%[+-]%d.%s", &sign, &first, &second);
	if(sign == '-') cout << sign;
	sscanf(second, "%*dE%d", &third);
	for(int i = 0; second[i]; i++) {
		if(second[i] == 'E') {
			second[i] = '\0';
			break;
		}
	}
	// cout << first << ' ' << third;
	if(third < 0) {
		cout << "0.";
		while(++third) {
			cout << 0;
		}
		cout << first;
		cout << second;
	} else {
		cout << first;
		for(int i = 0; second[i]; i++) {
			if(third-- == 0) {
				cout << '.';
			}
			cout << second[i];
		}
		while(third-- > 0) {
			cout << 0;
		}
	}
}
