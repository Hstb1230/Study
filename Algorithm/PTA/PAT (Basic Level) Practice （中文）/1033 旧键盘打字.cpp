#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	string wrong, normal;
	getline(cin, wrong);
	getline(cin, normal);
	map<char, bool> m;
	for(int i = 0; wrong[i]; i++)
		m[toupper(wrong[i])] = true;
	char output[100001] = {0};
	int t = 0;
	for(int i = 0; normal[i]; i++) {
		if(!(m.count('+') > 0 && isupper(normal[i])) && m.count(toupper(normal[i])) == 0)
			output[t++] = normal[i];
	}
	cout << output << endl;
}
