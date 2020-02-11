#include <iostream>
using namespace std;

int main() {
	string pat;
	getline(cin, pat);
	int count = 0, tmp = 0, a = 0, t = 0;
	for(int i = pat.length() - 1; i>= 0; i--) {
		if(pat[i] == 'T')
			t++;
		else if(pat[i] == 'A') {
			a++;
			tmp += t;
		} else if(pat[i] == 'P') {
			count += tmp;
			count %= 1000000007;
		}
//		printf("%d %d | %d %d\n", t, a, tmp, count);
	}
	cout << count;
}
