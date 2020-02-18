#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, D;
	double e;
	cin >> N >> e >> D;
	int k, flag;
	vector<double> E;
	int may = 0, must = 0;
	for(int i = 0; i < N; i++) {
		cin >> k;
		flag = 0;
		E.reserve(k);
		for(int j = 0; j < k; j++) {
			cin >> E[j];
			if(E[j] < e) flag++;
		}
		// cout << flag << endl;
		if(flag * 2 > k) {
			if(k > D)
				must++;
			else
				may++;
		}
	}
	printf("%.1f%% %.1f%%", 100.0 * may / N, 100.0 * must / N);
}
