#include <iostream>
#include <algorithm>
using namespace std;

int getMin(int * begin, int * end) {
	int * mini = begin;
	for(int * i = begin + 1; i < end; i++) {
		if(*i < *mini)
			mini = i;
	}
	return *mini;
}
int main() {
	int n;
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	// maxv is the maximun of the left part
	// minv is the minimun of the right part
	int maxv = a[0];
	int minv = a[n - 1];
	int b[n];
	int t = 0;
	for(int i = 0; i < n; i++) {
		if(a[i] < maxv) continue;
		maxv = a[i];
		if(a[i] > getMin(a + i, a + n)) continue;
		b[t++] = a[i];
	}
	printf("%d\n", t);
	sort(b, b + t);
	for(int i = 0; i < t; i++) {
		if(i) printf(" ");
		printf("%d", b[i]);
	}
}
