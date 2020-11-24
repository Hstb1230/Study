#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	string s;
	cin >> n;
	getline(cin, s);
	getline(cin, s);
	// 补齐空格
	if(s.length() % n != 0)
		s.append(n - s.length() % n, ' ');
	int col = s.length() / n;
	// int col = (s.length() + n - 1) / n;
	// 向上取整
	// 用ceil好像也行(多一步到浮点数的转换)
	// cout << ceil(double(s.length()) / n) << endl;
	for(int i = n; i > 0; i--) {
		for(int j = 0; j < col; j++) {
			//cout << int((s.length() + n - 1) / n * n - (i + j * n)) << ' ';
			int loc = col * n - (i + j * n);
			cout << s[loc];
		}
		cout << endl;
	}
	
	return 0;
}
