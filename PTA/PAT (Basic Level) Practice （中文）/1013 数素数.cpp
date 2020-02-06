#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(const int n) {
	int end = sqrt(n) + 1;
	for(int i = 2; i < end; i++) {
		if(n % i == 0) return false;
	}
	return true;
}

int getNextPrime(const int startPrime) {
	int prime = startPrime;
	if(prime == 2)
		prime = 3;
	else
		for(int i = prime + 2; ; i += 2) {
			if(isPrime(i)) {
				prime = i;
				break;
			}
		}
	return prime;
}

int main() {
	int m, n;
	cin >> m >> n;
	int prime = 2;
	for(int i = 1; i < m; i++) {
		// printf("%d:%d\n", i, prime);
		prime = getNextPrime(prime);
	}
	int flag = 0;
	for(int i = m; i <= n; i++) {
		// printf("%d:%d\n", i, prime);
		if(++flag % 10 != 1) cout << ' ';
		cout << prime;
		if(flag % 10 == 0) cout << endl;
		prime = getNextPrime(prime);
	}
}
