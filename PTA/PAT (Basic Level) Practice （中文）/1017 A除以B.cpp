#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	string a;
	int b;
	cin >> a >> b;
	const int len = a.length();
	int q[len], r, t = 0;
	for(int i = 0; i < len; i++) {
		a[i] -= '0';
		q[t] = (int)a[i] / b;
		r = a[i] % b;
		t++;
		if(i + 1 == len) break;
		a[i + 1] += r * 10;
	}
	
	// �����Ϊ1λ, �������ж�λ, ����һλ��Ϊ0
	if(t == 1 || q[0] > 0)
		cout << q[0];
	for(int i = 1; i < t; i++) {
		cout << q[i];
	}
	cout << " " << r;
}
