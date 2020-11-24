#include <iostream>
using namespace std;

void printSameChar(int count, char c) {
	while(count--)
		cout << c;
}

int main() {
	int n;
	cin >> n;
	printSameChar(n / 100, 'B');
	n %= 100;
	printSameChar(n / 10, 'S');
	n %= 10;
	for(int i = 1; i <= n; i++) {
		cout << i;
	}
}
