#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	bool pass = true;
	while(n--) {
		char s[19];
		cin >> s;
		int w[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
		int z = 0;
		for(int i = 0; i < 17; i++) {
			z += (s[i] - '0') * w[i];
		}
		z %= 11;
		char * m = "1 0 X 9 8 7 6 5 4 3 2";
		if(m[z * 2] == s[17]) continue;
		pass = false;
		cout << s << endl;
	}
	if(pass) cout << "All passed";
}
