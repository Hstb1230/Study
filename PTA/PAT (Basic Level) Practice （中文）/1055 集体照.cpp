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

void printPeople(vector<people> p, int K) {
	printf("----\n");
	int every = p.size() / K;
	int m = p.size() % K + every;
	for(int i = 0; i < p.size(); i++) {
		printf("%s %d\n", p[i].name.c_str(), p[i].high);
		if(--m == 0) {
			m = every;
			printf("\n");
		}
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
//	printPeople(p, K);
	int every = N / K;
	int m = every + N % K, flag;
	for(int i = 0; i < N; i += m, m = every) {
		flag = 0;
		for(int j = (i + m - 1) - m % 2; j >= i; j -= 2) {
			if(flag++ > 0) printf(" ");
			printf("%s", p[j].name.c_str());
		}
//		printf(" |");
		for(int j = i; j < i + m; j+= 2) {
			if(flag++ > 0) printf(" ");
			printf("%s", p[j].name.c_str());
		}
		printf("\n");
	}
}
