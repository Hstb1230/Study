#include <iostream>
#include <cmath>
using namespace std;

bool isVaildNum(string s) {
	int loc_point = -1;
	double num = 0;
	int len = s.length();
	bool flag = true;
	for(int i = (s[0] == '-' ? 1 : 0); i < len && flag; i++) {
//		printf("[%d] %c %lf\n", i, s[i], num);
		if(s[i] == '.') {
			// .x -.x 1.x.
			if(loc_point != -1 || i == 0 || (i == 1 && s[0] == '-'))
                flag = false;
            else
				loc_point = i;
//			printf("point in %d\n", loc_point);
		} else if(!isdigit(s[i])) {
			flag = false;
		} else {
			if(loc_point == -1) {
				num *= 10;
				num += s[i] - '0';
			} else {
				if(i - loc_point > 2) // && s[i] != '0')
					flag = false;
				else
					num += (s[i] - '0') / pow(10, i - loc_point);
			}
			if(num > 1000)
				flag = false;
		}
	}
	return flag;
}

int main() {
	int N;
	cin >> N;
	string s;
	double num, sum = 0;
	int count = 0;
	for(int i = 0; i < N; i++) {
		cin >> s;
		if(!isVaildNum(s)) {
			printf("ERROR: %s is not a legal number\n", s.c_str());
		} else {
			count++;
			sscanf(s.c_str(), "%lf", &num);
			sum += num;
		}
	}
	if(count == 0)
	    printf("The average of 0 numbers is Undefined");
	else if(count == 1)
		printf("The average of 1 number is %.2lf", sum);
	else
		printf("The average of %d numbers is %.2lf", count, sum / count);
}
