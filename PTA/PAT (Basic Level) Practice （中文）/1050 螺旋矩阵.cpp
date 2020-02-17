#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

void printArray(int * a, int n) {
	for(int i = 0; i < n; i++) {
		if(i > 0) cout << ' ';
		cout << a[i];
	}
	cout << endl;
}

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	int N;
	cin >> N;
	int a[N];
	for(int i = 0; i < N; i++)
		cin >> a[i];
	sort(a, a + N, cmp);
//	printArray(a, N);
	int m = N, n = 1;
	int tmp = m;
	while(--tmp > n) {
		if(N % tmp == 0) {
			m = tmp;
			n = N / tmp;
		}
	}
//	printf("%d %d\n", m, n);
	int b[m][n];
	memset(b, 0, sizeof(b));
	int i = 0, j = 0;
	char d = 'R';
	for(int t = 0; t < N; ) {
//		printf("%d %d\n", i, j);
		b[i][j] = a[t++];
		if(d == 'R') {
			if(j + 1 < n && b[i][j + 1] == 0)
				j++;
			else {
				d = 'D';
				i++;
			}
		} else if(d == 'D') {
			if(i + 1 < m && b[i + 1][j] == 0)
				i++;
			else {
				d = 'L';
				j--;
			}
		} else if(d == 'L') {
			if(j - 1 >= 0 && b[i][j - 1] == 0)
				j--;
			else {
				d = 'U';
				i--;
			}
		} else if(d == 'U') {
			if(b[i - 1][j] == 0)
				i--;
			else {
				d = 'R';
				j++;
			}
		}
	}
	for(int x = 0; x < m; x++) {
		if(x > 0)
			cout << endl;
		for(int y = 0; y < n; y++) {
			if(y > 0) cout << ' ';
			cout << b[x][y];
		}
	}
}
