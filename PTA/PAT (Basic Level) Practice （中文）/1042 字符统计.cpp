#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void countChar(string s, map<char, int> & chars) {
	for(int i = s.length() - 1; i >= 0; i--) {
		if(isalpha(s[i]))
			chars[tolower(s[i])]++;
	}
}

bool cmp(pair<char, int> a, pair<char, int> b) {
	return (a.second > b.second || (a.second == b.second && a.first < b.first));
}

int main() {
	string s;
	getline(cin, s);
	map<char, int> chars;
	countChar(s, chars);
	vector< pair<char, int> > v(chars.begin(), chars.end());
	sort(v.begin(), v.end(), cmp);
	printf("%c %d", v[0].first, v[0].second);
}
