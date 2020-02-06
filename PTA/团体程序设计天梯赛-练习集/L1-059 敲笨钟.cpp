#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	n++;
	
	string s;
	
	while(n--) {
		
		getline(cin, s);
		if(s == "") continue;

//		if(s.substr(s.find('.') - 3, 3) != "ong" || s.substr(s.find(',') - 3, 3) != "ong") {
//			cout << "Skipped" << endl;
//			continue;
//		}
		
		if(s.find("ong,") == string::npos || s.find("ong.") == string::npos) {
			cout << "Skipped" << endl;
			continue;
		}
		
		size_t beg = string::npos;
		for(int i = 0; i < 3; i++) {
			beg = s.find_last_of(' ', beg) - 1;
		}
		beg += 2;
		s.replace(beg, s.length() - 1 - beg, "qiao ben zhong");
		cout << s << endl;
	}
}
