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

	int factor1 = get_min_multiple(k, m1 * m2) / m1;
	int factor2 = get_min_multiple(k, m1 * m2) / m2;
//	int factor3 = get_min_multiple(k, m1 * m2);
//	printf("%d %d %d\n", factor1, factor2, factor3);
	// 化成以 K和m1*m2的最小公倍数 为分母的分数形式
	n1 *= factor1;
	n2 *= factor2;
	m2 = m1 = get_min_multiple(k, m1 * m2);
	// 因为分数1可能小于分数2, 交互
	if(n1 > n2) {
		int tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
//	printf("%d/%d %d/%d\n", n1, m1, n2, m2);

	int diff = m1 / k;
	int t = 0;
	int a[10000];
	// 找第一个最简分数的分子
	int first = n1 / diff + 1;
	int end = n2 / diff + 1;
	if(n2 % diff == 0) end--;
//	printf("%d\n", first);
	for(int i = first; i < end; i++) {
		if(get_max_factor(i, k) == 1) {
			a[t++] = i;
		}
	}
	
	for(int i = 0; i < t; i++) {
		if(i > 0) printf(" ");
		printf("%d/%d", a[i], k);
	}
}
