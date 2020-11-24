#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

char upper(char c) {
	if(c >= 'a' && c <= 'z')
		c = 'A' + (c - 'a');
	return c;
}

bool cmp(pair<char, int> a, pair<char, int> b) {
	return a.second < b.second;
}

int main() {
	string normal, wrong;
	getline(cin, normal);
	getline(cin, wrong);
	map<char, int> m;
	for(int i = 0; normal[i]; i++) {
		if(m.count(upper(normal[i])) == 0)
			m[upper(normal[i])] = i;
	}
	for(int i = 0; wrong[i]; i++) {
		m.erase(upper(wrong[i]));
	}
	vector< pair<char, int> > v(m.begin(), m.end());
	sort(v.begin(), v.end(), cmp);
	for(int i = 0; i < v.size(); i++) {
		cout << v[i].first;
	}
}
