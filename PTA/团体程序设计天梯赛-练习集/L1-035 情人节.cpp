#include <iostream>
using namespace std;

int main() {
	string p, p2, p14;
	int i = 0;
	while(true) {
		cin >> p;
		if(p == ".") break;
		if(++i == 2) {
			p2 = p;
		} else if(i == 14) {
			p14 = p;
		}
	}
	if(i >= 14) {
		printf("%s and %s are inviting you to dinner...", p2.c_str(), p14.c_str());
	} else if(i >= 2) {
		printf("%s is the only one for you...", p2.c_str());
	} else {
		printf("Momo... No one is for you ...");
	}
}
