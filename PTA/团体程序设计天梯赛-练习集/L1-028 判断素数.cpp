#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) {
	// 1不是素数(绝了)
	if(n == 1) return false;
	int end = sqrt(n) + 1;
	for(int i = 2; i < end; i++) {
		if(n % i == 0) return false;
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	int num;
	while(n--) {
		cin >> num;
		printf("%s\n", isPrime(num) ? "Yes" : "No");
	}
}
