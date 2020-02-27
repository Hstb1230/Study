#include <iostream>
#include <algorithm>
using namespace std;

void print_array(int * a, int n) {
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main() {
	int n;
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n);
//	print_array(a, n);
	int sum = a[0];
	for(int i = 1; i < n; i++) {
//		cout << sum << endl;
		sum = (sum + a[i]) / 2;
	}
	cout << sum << endl;
}
