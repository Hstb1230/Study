#include <iostream>
using namespace std;

typedef struct {
	int full;
	int choose;
} problem;

int main() {
	int n, m;
	cin >> n >> m;
	problem p[m];
	for(int i = 0; i < m; i++)
		cin >> p[i].full;
	for(int i = 0; i < m; i++)
		cin >> p[i].choose;
	int score = 0, input;
	for(int i = 0; i < n; i++) {
		score = 0;
		for(int j = 0; j < m; j++) {
			cin >> input;
			if(input == p[j].choose)
				score += p[j].full;
		}
		cout << score << endl;
	}

}
