#include <iostream>
using namespace std;

int main() {
	/*
	string date;
	cin >> date;
	string day, month, year;
	int start = 0;
	for(int i = 0; date[i]; i++) {
		if(date[i] == '-') {
			if(month == "") {
				month.assign(date, start, i - start);
				start = i + 1;
			} else if(day == "") {
				day.assign(date, start, i - start);
				start = i + 1;
			}
		}
	}
	year.assign(date, start, date.length() - start);
	printf("%s-%s-%s", year.c_str(), month.c_str(), day.c_str());
	*/
	// 最简单的方法
	int year, month, day;
	scanf("%d-%d-%d", &month, &day, &year);
	printf("%04d-%02d-%02d", year, month, day);
}
