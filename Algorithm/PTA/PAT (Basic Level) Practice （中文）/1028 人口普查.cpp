#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	char name[6];
	int year;
	int month;
	int day;
	int time;
} man;

bool cmp(man a, man b) {
	return a.time < b.time;
}

int main() {
	int n;
	cin >> n;
	vector<man> v(n);
	int min = 0, max = 0, t = 0;
	while(n--) {
		scanf("%s %d/%d/%d", &v[t].name, &v[t].year, &v[t].month, &v[t].day);
		v[t].time = v[t].year * 1e4 + v[t].month * 1e2 + v[t].day;
		if(v[t].time > 20140906 || v[t].time < 18140906)
			continue;
		if(v[t].time < v[min].time)
			min = t;
		else if(v[t].time > v[max].time)
			max = t;
//		printf("%d %d %d %d %d\n", v[t].time, v[min].time, v[max].time, v[t].time < v[min].time, v[t].time > v[max].time);
		t++;
	}
//	for(vector<man>::iterator it = v.begin(); it != v.end(); it++) {
//		printf("%s %d\n", it->name, it->time);
//	}
	// 排序会超时
	// erase也会
//	 sort(v.begin(), v.end(), cmp);
	printf("%d", t);
	if(t > 0)
//		printf("%d %s %s\n", v.begin()->name, v.end()->name);
		printf(" %s %s\n", v[min].name, v[max].name);
}
