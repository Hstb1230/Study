#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	long long a, b, c;
	for(int i = 1; i <= n; i++) {
		cin >> a >> b >> c;
		printf("Case #%d: ", i);
		if(a + b > c) {
			cout << "true";
		} else {
			cout << "false";
		}
		cout << endl;
	}
}
