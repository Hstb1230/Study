#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<string> strs;

int get_char_type(const char c);

void print_strs(const strs ss) {
	cout << "AI: ";
	for(int i = 0; i < ss.size(); i++) {
		cout << ss[i];
	}
//	cout << '|';
	cout << endl;
}

int get_char_type(const char c) {
	if(c == '\0') return -1;
	if(c == ' ') return 0;
	if(
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9')
	)
		return 1;
	return 2;
}

void splice_str(const string s, strs & ss) {
	ss.clear();
	int start = -1, end = -1;
	int last_type = 0;
	for(int i = 0; i <= s.length(); i++) {
		// cout << s[i] << ' ' << get_char_type(s[i]) << endl;
		if(last_type != get_char_type(s[i])) {
			last_type = get_char_type(s[i]);
			if(start == -1) {
				start = i;
				continue;
			}
			end = i;
			ss.push_back(s.substr(start, end - start));
			start = end;
		}
	}
//	for(int i = 0; i < ss.size(); i++) {
//		cout << ss[i] << "|" << endl;
//	}
}

void str_to_low(string & s) {
	for(int i = 0; i < s.length(); i++) {
		if(s[i] >= 'A' && s[i] <= 'Z' && s[i] != 'I')
			s[i] = 'a' + (s[i] - 'A');
	}
}

int main() {
	int n;
	cin >> n;
	n++;

	while(n--) {
		string s;
		getline(cin, s);
		if(s == "") continue;

		cout << s << endl;

		strs ss;
		splice_str(s, ss);

		for(int i = 0; i < ss.size(); i++) {
			if(get_char_type(ss[i][0]) == 0) {
				if(i + 1 < ss.size() && get_char_type(ss[i + 1][0]) == 2) {
					ss.erase(ss.begin() + i);
					i--;
					continue;
				}
				if(i + 1 == ss.size()) {
					ss.erase(ss.end());
					continue;
				}
				if(ss[i].length() > 1) ss[i] = " ";
			}
			
			// 大写转小写(除了I)
			str_to_low(ss[i]);
			
			if(get_char_type(ss[i][0]) == 2) {
				// 因为所以半角符号都会被分割到一个字符集中, 所以需要替换里面的?为!
				replace(ss[i].begin(), ss[i].end(), '?', '!');
			} else if(ss[i] == "I" || ss[i] == "me")
                // 替换I/me为you
				ss[i] = "you";
			else if(i > 1 && ss[i] == "you") {
				// 替换can you / could you
				if(ss[i - 2] == "can") {
					ss[i - 2] = "I";
					ss[i] = "can";
				}
				if(ss[i - 2] == "could") {
					ss[i - 2] = "I";
					ss[i] = "could";
				}
			}
		}

		print_strs(ss);
	}
}
