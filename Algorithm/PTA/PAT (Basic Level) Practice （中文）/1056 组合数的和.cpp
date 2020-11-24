#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int suma = 0, sumb = 0, input;
	for(int i = 0; i < n; i++) {
		cin >> input;
		suma += (n - 1) * input;
		sumb += (n - 1) * input;
	}
	cout << suma * 10 + sumb;
}
