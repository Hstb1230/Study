#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int sum = 0;
	int cum = 1;
	for(int i = 1; i <= n; i++) {
		cum *= i;
		sum += cum;
	}
	cout << sum;
}
