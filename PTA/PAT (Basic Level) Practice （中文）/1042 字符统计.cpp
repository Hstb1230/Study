#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void countChar(string s, int chars[]) {
	for(int i = s.length() - 1; i >= 0; i--) {
		if(isalpha(s[i]))
			chars[tolower(s[i]) - 'a']++;
	}
}

void printChars(const int * chars) {
	for(int i = 0; i < 26; i++) {
		if(chars[i] > 0) {
			printf("%c: %d\n", 'a' + i, chars[i]);
		}
	}
}

int findMax(const int * chars) {
	int max = 0;
	for(int i = 0; i < 26; i++) {
		if(chars[i] > chars[max])
			max = i;
	}
	return max;
}

int main() {
	string s;
	getline(cin, s);
	int chars[26] = {0};
	countChar(s, chars);
//	printChars(chars);
	int max = findMax(chars);
	printf("%c %d", 'a' + max, chars[max]);
}
