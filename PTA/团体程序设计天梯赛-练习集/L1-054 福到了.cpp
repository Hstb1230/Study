#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	char c;
	int n;
	scanf("%c%d%*[\n\r]", &c, &n);
	vector<string> s(n);
	for(int i = 0; i < n; i++) {
		getline(cin, s[i]);
	}
	const vector<string> cs(s);
	reverse(s.begin(), s.end());
	bool flag = true;
	for(int i = 0; i < n; i++) {
		reverse(s[i].begin(), s[i].end());
		if(flag && cs[i] != s[i]) {
			flag = false;
		}
	}
	if(flag) cout << "bu yong dao le" << endl;
	for(int i = 0; i < n; i++) {
		replace(s[i].begin(), s[i].end(), '@', c);
		cout << s[i] << endl;
	}
}
