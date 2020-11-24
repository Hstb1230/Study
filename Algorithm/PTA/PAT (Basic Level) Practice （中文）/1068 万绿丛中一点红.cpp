#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

vector< vector<int> > pic;

bool is_diff(int i, int j, int diff) {
	int m = pic[0].size(), n = pic.size();
	int center = pic[i][j];
	diff++;
	bool flag = false;
	while(true) {
		// Last Line
		if(i > 0) {
			if(j > 0 && fabs(center - pic[i - 1][j - 1]) < diff)
				break;
			if(fabs(center - pic[i - 1][j]) < diff)
				break;
			if(j + 1 < m && fabs(center - pic[i - 1][j + 1]) < diff)
				break;
		}
		// Now Line
		if(j > 0 && fabs(center - pic[i][j - 1]) < diff)
			break;
		if(j + 1 < m && fabs(center - pic[i][j + 1]) < diff)
			break;
		// Next line
		if(i + 1 < n) {
			if(j > 0 && fabs(center - pic[i + 1][j - 1]) < diff)
				break;
			if(fabs(center - pic[i + 1][j]) < diff)
				break;
			if(j + 1 < m && fabs(center - pic[i + 1][j + 1]) < diff)
				break;
		}
		flag = true;
		break;
	}
	return flag;
}

int main() {
	int m, n, tol;
	cin >> m >> n >> tol;
	map<int, int> value;
	pic.resize(n);
	for(int i = 0; i < n; i++) {
		pic[i].resize(m);
		for(int j = 0; j < m; j++) {
			scanf("%d", &pic[i][j]);
			value[pic[i][j]]++;
		}
	}

	int flag = 0;
	int x, y;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(value[pic[i][j]] > 1) continue;
			if(is_diff(i, j, tol)) {
				if(++flag > 1) break;
				x = i + 1;
				y = j + 1;
			}
		}
	}
	if(flag == 0) {
		printf("Not Exist\n");
	} else if(flag > 1) {
		printf("Not Unique\n");
	} else {
		printf("(%d, %d): %d\n", y, x, pic[x - 1][y - 1]);
	}
}
