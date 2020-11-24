#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		
		int a, b, c;
		a = b = c = 0;
		int loc = 0; // 0/PÇ° 1/TÇ° 2/Tºó
		
		bool flag = true;
		for(int i = 0; i < s.length(); i++) {
			if(s[i] == 'A') {
				if(loc == 0)
					a++;
				else if(loc == 1)
					b++;
				else if(loc == 2)
					c++;
			} else if(s[i] == 'P') {
				if(loc == 0)
					loc = 1;
				else {
					flag = false;
					break;
				}
			} else if(s[i] == 'T') {
				if(loc == 1)
					loc = 2;
				else {
					flag = false;
					break;
				}
			} else {
				flag = false;
				break;
			}
		}
        if(loc != 2)
			flag = false;
//        printf("%d %d %d %d\n", a, b, c, flag);
		while(flag) {
//			flag = (b > 0 && a * b == c);
//			break;
			if(b == 0) {
				flag = false;
				break;
			} else if(b == 1) {
				flag = (a == c);
			} else {
				while(b > 1) {
					b -= 1;
					c -= a;
				}
				flag = (a == c);
			}
			break;
		}

		if(flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}
