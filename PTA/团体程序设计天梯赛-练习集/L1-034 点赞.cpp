#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

map<int, int> m;
typedef pair<int, int> mp;

bool cmp(mp a, mp b) {
	if(a.second == b.second) return a.first > b.first;
	else return a.second > b.second;
}

int main() {
	int n;
	cin >> n;
	int k, f;
	
	while(n--) {
		cin >> k;
		while(k--) {
			cin >> f;
			if(m.count(f)) m[f]++;
			else m[f] = 1;
		}
	}
	
	vector<mp> m_vec(m.begin(), m.end());
	sort(m_vec.begin(), m_vec.end(), cmp);
	
//	for(int i = 0; i < m_vec.size(); i++) {
//		cout << m_vec[i].first << ' ' << m_vec[i].second << endl;
//	}

	cout << m_vec[0].first << ' ' << m_vec[0].second << endl;
	
	return 0;
}
