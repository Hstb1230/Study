#include <iostream>
#include <map>
using namespace std;

void printMap(map<char, int> m) {
	for(map<char, int>::iterator it = m.begin(); it != m.end(); it++) {
		printf("%c %d\n", it->first, it->second);
	}
}

int main() {
	string a, b;
	getline(cin, a);
	getline(cin, b);
	map<char, int> m;
	for(int i = b.length() - 1; i >= 0; i--)
		m[b[i]]++;
//	printMap(m);
	for(int i = a.length() - 1; i >= 0; i--)
		if(m.count(a[i]))
			m[a[i]]--;
//	printMap(m);
	int count = 0;
	for(map<char, int>::iterator it = m.begin(); it != m.end(); it++) {
		if(it->second > 0) count += it->second;
	}
	if(count == 0) {
		printf("%s %d", "Yes", a.length() - b.length());
	} else {
		printf("%s %d", "No", count);
	}
}
