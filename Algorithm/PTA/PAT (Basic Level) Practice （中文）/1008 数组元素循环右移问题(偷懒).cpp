#include <iostream>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	m %= n;
	int a[n]; //也可以是2n
	for(int i = 0; i < n; i++) {
		cin >> a[(m + i) % n];
	}
	for(int i = 0; i < n; i++) {
		if(i != 0) cout << ' ';
		cout << a[i];
	}
}
