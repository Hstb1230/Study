#include <iostream>
using namespace std;

// ����yearתtime����
void y2t(int year, int time[]) {
	int i = 3;
	while(year > 0) {
		time[i--] = year % 10;
		year /= 10;
	}
}

// time����
void ti(int time[]) {
	++time[3];
	for(int i = 3; i > 0; i--) {
		if(time[i] > 9) {
			time[i] = 0;
			time[i - 1]++;
		}
	}
}

// ͳ��time���ж��ٲ�ͬ����
int tc(const int time[]) {
	int f[10] = {0};
	int c = 0;
	for(int i = 0; i < 4; i++) {
		if(++f[time[i]] == 1) c++;
	}
	return c;
}

// ���ʱ��
void pt(int time[]) {
	for(int i = 0; i < 4; i++) {
		cout << time[i];
	}
	cout << endl;
}

int main() {
	int y, n;
	int time[4] = {0};
	cin >> y >> n;
	y2t(y, time);
	int t = 0;
	while(true) {
		// cout << tc(time) << endl;
		// pt(time);
		if(tc(time) == n) break;
		t++;
		ti(time);
	}
	
	cout << t << ' ';
	pt(time);
}
