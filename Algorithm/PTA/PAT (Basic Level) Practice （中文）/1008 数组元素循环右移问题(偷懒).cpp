#include <iostream>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	m %= n;
	int a[n]; //Ҳ������2n
	for(int i = 0; i < n; i++) {
		cin >> a[(m + i) % n];
	}
	for(int i = 0; i < n; i++) {
		if(i != 0) cout << ' ';
		cout << a[i];
	}
}
