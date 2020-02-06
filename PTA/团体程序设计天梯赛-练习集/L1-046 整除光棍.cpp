#include <iostream>
using namespace std;
// 大数求解
// 模拟除法过程
// 做除法时, 一般只看被除数中, 除以除数的那一小部分,
// 所以每次剩下的余数, 放在最开头就又是被除数(即x10)
// 而之所以＋1, 是因为被除数是11111...111
int main() {
	int s = 0;
	int x, n = 0;
	cin >> x;
	while(s < x) {
		n++;
		s *= 10;
		s += 1;
	}
	while(true) {
		cout << (int)(s / x);
		s %= x;
		if(s == 0) break;
		s *= 10;
		s += 1;
		n++;
	}
	cout << ' ' << n;
}
