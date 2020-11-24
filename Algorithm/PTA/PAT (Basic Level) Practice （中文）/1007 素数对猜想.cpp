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

int main() {
	int n;
	cin >> n;
	
	
	int last = 2;
	int count = 0;
	
	for(int i = 2; i <= n; i++) {
		if(isPrime(i)) {
			// cout << i << endl;
			if(i - last == 2) {
				count++;
			}
			last = i;
		}
	}
	cout << count;
}
