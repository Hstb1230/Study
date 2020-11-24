#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void spliceString(string str, char splice, vector<string> & strs, bool containSplice = false) {
	strs.clear();
	int start = 0;
	for(int i = 0; i <= str.length(); i++) {
		if(str[i] == splice || str[i] == '\0') {
			if(i - start > 0)
				strs.push_back(str.substr(start, i - start));
			if(containSplice)
				strs.push_back(str.substr(start, 1));
			start = i + 1;
		}
	}
}

void printStringArray(const vector<string> ss) {
	for(int i = 0; i < ss.size(); i++) {
		if(i != 0) cout << ' ';
		cout << ss[i];
	}
	cout << endl;
}

int main() {
	string s;
	getline(cin, s);
	vector<string> ss;
	spliceString(s, ' ', ss);
	reverse(ss.begin(), ss.end());
	printStringArray(ss);
}
