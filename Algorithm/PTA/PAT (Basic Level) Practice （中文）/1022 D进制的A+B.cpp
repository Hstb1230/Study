#include <iostream>
#include <vector>
using namespace std;

int main() {
	long long a, b, d;
	cin >> a >> b >> d;
	long long c = a + b;
	if(c == 0 || d == 10) {
		cout << c;
	} else {
		vector<int> e;
		while(c > 0) {
			e.push_back(c % d);
			c /= d;
		}
		for(vector<int>::reverse_iterator it = e.rbegin(); it != e.rend(); it++) {
			cout << *it;
		}
	}

}
