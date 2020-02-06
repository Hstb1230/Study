#include <iostream>
using namespace std;

void reverse(int num[], const int start, const int end) {
	int to = (end + start) / 2 + 1;
	for(int i = start; i < to; i++) {
		int tmp = num[i];
		num[i] = num[end - (i - start)];
		num[end - (i - start)] = tmp;
	}
}

void printIntArray(const int num[], const int count) {
	for(int i = 0; i < count; i++) {
		if(i != 0) cout << ' ';
		cout << num[i];
	}
	cout << endl;
}

int main() {
	int n, m;
	cin >> n >> m;
	m %= n;
	int a[n]; //也可以是2n
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	
	reverse(a, 0, n - m - 1);
//	printIntArray(a, n);
	
	reverse(a, n - m, n - 1);
//	printIntArray(a, n);

	reverse(a, 0, n - 1);
	printIntArray(a, n);
}
