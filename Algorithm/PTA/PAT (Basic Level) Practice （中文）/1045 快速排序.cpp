#include <iostream>
using namespace std;

void printArray(int b[], int t) {
	printf("b: ");
	for(int i = 0; i < t; i++) {
		printf("%d ", b[i]);
	}
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	// maxv is the maximun of the left part
	int maxv = a[0];
	// b is the result
	int b[n];
	// t is the size of b
	int t = 0;
	for(int i = 0; i < n; i++) {
		// 判断 a当前元素 是否比 b的最后一个元素 大
		// 如果是, 就说明b中有不是主元的元素,
		// 需要回溯, 将这些元素踢除
		// if a[i] > b[end], then the b has some wrong keys.
		if(t > 0 && b[t - 1] > a[i]) {
			for(int j = t - 1; j >= 0; j--) {
				if(b[j] > a[i]) t--;
				else break;
			}
//			printArray(b, t);
		}
		// the key must be maximun of left.
		if(a[i] < maxv) continue;
		maxv = a[i];
		// the key must min than right
		if(i + 1 < n && a[i] > a[i + 1]) continue;
		b[t++] = a[i];
//		printArray(b, t);
	}
	printf("%d\n", t);
	for(int i = 0; i < t; i++) {
		if(i > 0) printf(" ");
		printf("%d", b[i]);
	}
	printf("\n");
}
