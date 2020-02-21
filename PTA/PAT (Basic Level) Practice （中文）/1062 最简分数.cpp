#include <iostream>
using namespace std;

int get_max_factor(int a, int b) {
	if(b > a) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	int c;
	while((c = a % b) != 0) {
		a = b;
		b = c;
	}
	return b;
}

int get_min_multiple(int a, int b) {
	return a / get_max_factor(a, b) * b;
}

int main() {
	int n1, m1, n2, m2, k;
	scanf("%d/%d", &n1, &m1);
	scanf("%d/%d", &n2, &m2);
	scanf("%d", &k);

	int factor1 = get_min_multiple(m1, m2) / m1;
	int factor2 = get_min_multiple(m1, m2) / m2;
//	printf("%d %d\n", factor1, factor2);

	n1 *= factor1;
	m2 = m1 *= factor1;
	n2 *= factor2;
//	printf("%d/%d %d/%d\n", n1, m1, n2, m2);

	int diff = m1 / k;
	int t = 0;
	int a[10000];
	// 找最小符合条件的数
	int first = n1 + 1;
	for(; first < n2; first++) {
		if(first % diff == 0) break;
	}
	for(int i = first; i < n2; i += diff) {
		if(get_max_factor(i, m1) == diff) {
			a[t++] = i / diff;
		}
	}
	
	for(int i = 0; i < t; i++) {
		if(i > 0) printf(" ");
		printf("%d/%d", a[i], k);
	}
}
