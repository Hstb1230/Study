#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	string s;
	cin >> n;
	getline(cin, s);
	getline(cin, s);
	// ����ո�
	if(s.length() % n != 0)
		s.append(n - s.length() % n, ' ');
	int col = s.length() / n;
	// int col = (s.length() + n - 1) / n;
	// ����ȡ��
	// ��ceil����Ҳ��(��һ������������ת��)
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
