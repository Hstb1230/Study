#include <iostream>
using namespace std;

int main() {
	string s1, s2, s3, s4;
	getline(cin, s1);
	getline(cin, s2);
	getline(cin, s3);
	getline(cin, s4);

	int day = 0;
	int hour;
	int second;

	int flag = 0;
	for(int i = 0; s1[i] && s2[i]; i++) {
		if(s1[i] != s2[i]) continue;
		
		if(day == 0 && s1[i] >= 'A' && s1[i] <= 'G') {
			day = (s1[i] - 'A') % 7 + 1;
			flag++;
		} else if(day == 0) {
			continue;
		} else {
			//printf("%c %d %d\n", s1[i], day, flag);
			if(s1[i] >= 'A' && s1[i] <= 'N') {
				hour = 10 + (s1[i] - 'A');
			} else if(isdigit(s1[i])) {
				hour = s1[i] - '0';
			} else {
				continue;
			}
			break;
		}
	}

	for(int i = 0; s3[i] && s4[i]; i++) {
		if(s3[i] != s4[i]) continue;
		if(!isalpha(s3[i])) continue;
		second = i % 60;
		break;
	}

	string s[] = {"", "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
	printf("%s %02d:%02d", s[day].c_str(), hour, second);
}
