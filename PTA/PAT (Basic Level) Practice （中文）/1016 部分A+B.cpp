#include <iostream>
using namespace std;

int main() {
	string a, b;
	int da, db;
	cin >> a >> da >> b >> db;
	int pa = 0, pb = 0;
	for(int i = 0; a[i]; i++) {
		if(a[i] - '0' == da) {
			pa *= 10;
			pa += da;
		}
	}
	for(int i = 0; b[i]; i++) {
		if(b[i] - '0' == db) {
			pb *= 10;
			pb += db;
		}
	}
	cout << pa + pb;
}
