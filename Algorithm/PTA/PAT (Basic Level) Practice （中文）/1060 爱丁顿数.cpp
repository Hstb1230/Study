#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n, greater<int>());
	int e = 0;
	for(int i = 0; i < n; i++) {
		if(a[i] > i + 1) e++;
	}
	cout << e;
}
