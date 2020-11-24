#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	string name;
	int high;
} people;

bool cmp(people a, people b) {
	if(a.high == b.high)
		return a.name < b.name;
	else
		return a.high > b.high;
}

void printPeople(vector<people> p) {
	printf("----\n");
	for(int i = 0; i < p.size(); i++) {
		printf("%s %d\n", p[i].name.c_str(), p[i].high);
	}
	printf("----\n");
}

int main() {
	int N, K;
	cin >> N >> K;
	int length = N / K;
	vector<people> p(N);
	for(int i = 0; i < N; i++) {
		cin >> p[i].name >> p[i].high;
	}
	sort(p.begin(), p.end(), cmp);
//	printPeople(p);
	int every = N / K;
	int m = every + (N % K);
	int highest, center, j = 0, begin;
	for(int i = 0; i < N; i++) {
		if(j == 0) {
			if(i > 0) printf("\n");
//			cout << m << endl;
			highest = i;
			center = m / 2;
			begin = i + m - 1 - (m % 2);
		} else {
			printf(" ");
		}
		if(j < center) {
			printf("%s", p[begin].name.c_str());
			begin -= 2;
		} else if(j == center) {
			printf("%s", p[highest].name.c_str());
			begin = highest + 2;
		} else if(j > center) {
			printf("%s", p[begin].name.c_str());
			begin += 2;
		}
		if(++j == m) {
			j = 0;
			if(m != every) m = every;
		}
	}
}
