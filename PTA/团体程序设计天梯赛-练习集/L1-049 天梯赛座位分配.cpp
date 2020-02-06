#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> m(n);
	for(int i = 0; i < n; i++) {
		cin >> m[i];
		m[i] *= 10;
	}
	const vector<int> cm(m);
	for(int i = 0; i < n; i++) {
		printf("#%d\n", i + 1);
		int loc = 0;
		int finish = 0;
		m = cm;
		while(m[i] > 0) {
			for(int j = 0; j < n; j++) {
				if(m[j] <= 0) continue;
				loc++;
				m[j]--;
				if(j == i) {
					cout << loc;
					if(finish + 1 == n) loc++;
					if(m[j] % 10 == 0) cout << endl;
					else cout << ' ';
				}
				if(m[j] == 0) finish++;
			}
		}
	}
}
/*
4
3 4 5 2

1
1

*/
