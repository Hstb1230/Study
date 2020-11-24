#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	double sum = 0, input;
	for(int i = 0; i < n; i++) {
		cin >> input;
		sum += input * (n - i) * (i + 1);
	}
	printf("%.2f", sum);
}
