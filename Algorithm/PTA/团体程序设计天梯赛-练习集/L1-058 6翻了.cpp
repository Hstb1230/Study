#include <iostream>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	
	int start, end;
	end = start = -1;

	for(int i = 0; s[i] || start != -1; i++) {
		if(start == -1 && s[i] == '6') {
			start = i;
		} else if(start != -1 && s[i] != '6') {
			end = i;
			// printf("%d %d\n", start, end);
			if(end - start > 9) {
				s.replace(s.begin() + start, s.begin() + end, "27");
			} else if(end - start > 3) {
				s.replace(s.begin() + start, s.begin() + end, "9");
			}
			//cout << s << endl;
			i = start;
			start = -1;
		}
	}
	cout << s << endl;
}
