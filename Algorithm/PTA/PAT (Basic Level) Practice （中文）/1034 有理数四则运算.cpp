#include <iostream>
#include <cmath>
using namespace std;

long long getMaxFactor(long long a, long long b) {
	a = fabs(a);
	b = fabs(b);
	long long c;
	while(true) {
		if(a < b) {
			long long tmp = a;
			a = b;
			b = tmp;
		}
//		printf("%d %d\n", a, b);
		c = a % b;
		if(c == 0) break;
		a = b;
		b = c;
	}
	return b;
}

void simplify(long long & a, long long & b) {
	if(a == 0) return;
	if(a == 1 || b == 1) return;
	long long factor = getMaxFactor(a, b);
	if(factor == 1) return;
	a /= factor;
	b /= factor;
}

void printAB(long long a, long long b) {
	if(b < 0) {
		a *= -1;
		b *= -1;
	}
	long long k = a / b;
	a = a % b;
	if(k < 0)
		a = fabs(a);
	b = fabs(b);
	if(k < 0 || a < 0)
		cout << '(';
	if(a == 0 || k != 0)
	    cout << k;
	if(k != 0 && a != 0)
		cout << ' ';
	if(a != 0)
		printf("%lld/%lld", a, b);
	if(k < 0 || a < 0)
		cout << ')';
}

void addAB(long long a1, long long b1, long long a2, long long b2, long long & a3, long long & b3) {
	if(a1 == 0) {
		a3 = a2;
		b3 = b2;
	} else if(a2 == 0) {
		a3 = a1;
		b3 = b1;
	} else {
		a3 = a1 * b2 + a2 * b1;
		b3 = b1 * b2;
	}
}

void subAB(long long a1, long long b1, long long a2, long long b2, long long & a3, long long & b3) {
	return addAB(a1, b1, -a2, b2, a3, b3);
}

void mulAB(long long a1, long long b1, long long a2, long long b2, long long & a3, long long & b3) {
	if(a1 == 0 || a2 == 0) {
		a3 = 0;
		return;
	}
	simplify(a1, b2);
	simplify(b1, a2);

//	cout << endl;
//	printf("%d/%d", a1, b1);
//	cout << ' ';
//	printf("%d/%d", a2, b2);
//	cout << ' ';

	a3 = a1 * a2;
	b3 = b1 * b2;

//	printf("%d/%d", a3, b3);
//	cout << endl;
}

void divAB(long long a1, long long b1, long long a2, long long b2, long long & a3, long long & b3) {
	if(a2 == 0) return;
	if(a1 == 0) {
		a3 = 0;
		return;
	}
	return mulAB(a1, b1, b2, a2, a3, b3);
}

int main() {
	long long a1, b1, a2, b2;
	scanf("%lld/%lld %lld/%lld", &a1, &b1, &a2, &b2);
	simplify(a1, b1);
	simplify(a2, b2);
//	return 0;
	int flag = 0;
	long long a3 = 1, b3 = 3;
	while(flag++ < 4) {
		printAB(a1, b1);
		switch(flag) {
			case 1:
				cout << " + ";
				addAB(a1, b1, a2, b2, a3, b3);
				break;
			case 2:
				cout << " - ";
				subAB(a1, b1, a2, b2, a3, b3);
				break;
			case 3:
				cout << " * ";
				mulAB(a1, b1, a2, b2, a3, b3);
				break;
			case 4:
				cout << " / ";
				divAB(a1, b1, a2, b2, a3, b3);
				break;
		}
		printAB(a2, b2);
		cout << " = ";
//		simplify(a3, b3);
		if(flag == 4 && a2 == 0)
			cout << "Inf";
		else
			printAB(a3, b3);
		cout << endl;
	}

}
