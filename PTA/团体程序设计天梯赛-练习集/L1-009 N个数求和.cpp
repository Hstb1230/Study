#include <iostream>
#include <cmath>
using namespace std;

void opt(int & z, int & a, int & b) {
	z += a / b;
	a %= b;
	// cout << a << ' ' << b << endl;
	if(a == 0) return;
	int tmp;
	int max = fabs(b), min = fabs(a);
	while(true) {
		tmp = max % min;
		if(tmp == 0) {
			a /= min;
			b /= min;
			break;
		} else {
			max = min;
			min = tmp;
		}
	}
}

int main() {
	int n;
	cin >> n;
	string s;
	int z = 0, a = 0, b = 1;
	while(n--) {
		cin >> s;
		bool symbol = false;
		int ai = 0, bi = 0;
		bool delimiter = false;
		for(int i = 0; s[i] != '\0'; i++) {
			if(s[i] == '-') {
				symbol = !symbol;
				continue;
			} else if(s[i] == '/') {
				delimiter = true;
				continue;
			}
			if(!delimiter) {
				ai *= 10;
				ai += s[i] - '0';
			} else {
				bi *= 10;
				bi += s[i] - '0';
			}
		}
		if(symbol) ai *= -1;
		// cout << a << '/' << b << endl;
		a = a * bi + ai * b;
		b = b * bi;
		opt(z, a, b);
		// cout << z << ' ' << sa << '/' << sb << endl;
	}
	// cout << sa << '/' << sb << endl;
	if(z != 0) cout << z;
	if(z != 0 && a != 0) cout << ' ';
	if(a != 0) cout << a << '/' << b << endl;
	if(z == 0 && a == 0) cout << '0' << endl;
}
