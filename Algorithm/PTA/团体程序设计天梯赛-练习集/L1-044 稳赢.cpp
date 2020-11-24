#include <iostream>
using namespace std;

int main() {
	int k;
	cin >> k;
	int count = 0;
	while(true) {
		string s;
		cin >> s;
		if(s == "End") {
			break;
		}
		if(count++ == k) {
			count = 0;
			cout << s << endl;
			continue;
		}
		if(s == "ChuiZi") {
			cout << "Bu" << endl;
		} else if(s == "JianDao") {
			cout << "ChuiZi" << endl;
		} else if(s == "Bu") {
			cout << "JianDao" << endl;
		}
	}
}
