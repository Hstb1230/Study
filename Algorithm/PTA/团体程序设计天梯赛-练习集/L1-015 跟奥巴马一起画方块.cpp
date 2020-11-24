#include <iostream>
using namespace std;

int main() {
	int n;
	char c;
	cin >> n >> c;
	for(int i = int(n * 0.5 + 0.5); i > 0; i--) {
		for(int j = n; j > 0; j--) cout << c;
		cout << endl;
	}
}
