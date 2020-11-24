#include <iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	string num[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
	int end = s.length();
	for(int i = 0; i < end; i++) {
		if(i > 0) cout << ' ';
		if(s[i] == '-')
			cout << "fu";
		else
			cout << num[s[i] - '0'];
	}

}
