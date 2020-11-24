#include <iostream>
using namespace std;

int main() {
	int n;
	char c;
	cin >> n >> c;
	const int line = (n + 1)* 0.5;
	bool flag;
	for(int j = line; j > 0; j--) {
		flag = (j == line || j == 1);
		for(int i = 0; i < n; i++) {
			cout << char((flag || i == 0 || i + 1 == n) ? c : ' ');
		}
		cout << endl;
    }
}
