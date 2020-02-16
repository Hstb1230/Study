#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	string a, b;
	cin >> a >> b;
	int len_a = a.length(), len_b = b.length();
	if(len_b < len_a) {
		b.insert(0, len_a - len_b, '0');
		len_b = b.length();
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	
	char cs[] = "0123456789JQK";
	string p;
	for(int i = 0; i < len_b; i++/*, cout << p << endl*/) {
		if(i >= len_a) {
//			cout << b[i] << endl;
			p.push_back(b[i]);
			continue;
		}
		if(i % 2 == 0) {
			p.push_back(cs[(b[i] - '0' + a[i] - '0') % 13]);
		} else {
			if(b[i] < a[i]) {
				p.push_back('0' + (b[i] - a[i] + 10));
			} else {
				p.push_back('0' + (b[i] - a[i]));
			}
		}
	}
	reverse(p.begin(), p.end());
	cout << p << endl;
}

