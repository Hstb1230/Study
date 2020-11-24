#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> iipair;

bool cmp(iipair a, iipair b) {
	return a.second > b.second;
}

int main() {
	int n;
	cin >> n;
	int school, score;
	map<int, int> m;
	while(n--) {
		cin >> school >> score;
		m[school] = m[school] + score;
	}
	vector<iipair> v(m.begin(), m.end());
	sort(v.begin(), v.end(), cmp);
	printf("%d %d\n", v.begin()->first, v.begin()->second);
}
