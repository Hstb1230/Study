#include <iostream>
#include <cstring>
using namespace std;

const char * low[] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
const char * high[] = {"tret", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};

string dexToMars(string s) {
	int d;
	sscanf(s.c_str(), "%d", &d);
	int dlow = d % 13;
	int dhigh = d / 13;
	s = "";
	if(dhigh > 0)
		s.append(high[dhigh]);
	if(dhigh > 0 && dlow > 0)
		s.append(1, ' ');
	if(dlow > 0 || d == 0)
		s.append(low[dlow]);
	return s;
}

int getLowIndex(string s) {
	int i;
	for(i = 0; i < 13; i++) {
		if(s == low[i]) break;
	}
	if(i == 13) i = 0;
	return i;
}

int getHighIndex(string s) {
	int i;
	for(i = 0; i < 13; i++) {
		if(s == high[i]) break;
	}
	if(i == 13) i = 0;
	return i;
}

int marsToDex(string s) {
	int space = s.find(' ');
	int dex = 0;
	string mlow, mhigh;
	if(space == string::npos) {
		dex = getHighIndex(s) * 13 + getLowIndex(s);
	} else {
		mhigh = s.substr(0, space);
		mlow = s.substr(space + 1);
		dex = getHighIndex(mhigh) * 13 + getLowIndex(mlow);
	}
	return dex;
}

int main() {
	int n;
	cin >> n;
	n++;
	while(n--) {
		string s;
		getline(cin, s);
		if(s == "") continue;
//		cout << s << endl;
		if(isdigit(s[0]))
			cout << dexToMars(s) << endl;
		else
			cout << marsToDex(s) << endl;
	}

}
