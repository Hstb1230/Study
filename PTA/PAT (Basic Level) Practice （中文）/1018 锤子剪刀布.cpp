#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int judge(const char & a, const char & b) {
	// printf("%c %c\n", a, b);
	if(a == b)
		return 0;
	if(
		(a == 'C' && b == 'J') ||
		(a == 'J' && b == 'B') ||
		(a == 'B' && b == 'C')
	)
		return 1;
	return 2;
}

bool cmp(pair<char, int> a, pair<char, int> b) {
//	printf("%c %d | %c %d\n", a.first, a.second, b.first, b.second);
	if(a.second == b.second)
		return a.first < b.first;
	return a.second > b.second;
}

int main() {
	int n;
	cin >> n;
	char ag, bg; // guess
	int r; // fight result
	map<char, int> ma, mb;
	ma['C'] = ma['J'] = ma['B'] = 0;
	mb['C'] = mb['J'] = mb['B'] = 0;
	vector<int> va(3), vb(3);
	while(n--) {
		cin >> ag >> bg;
		
		r = judge(ag, bg);
		va[r]++;
		if(r == 1)
			ma[ag]++;
			
		r = judge(bg, ag);
		vb[r]++;
		if(r == 1)
			mb[bg]++;
		
	}
	// 输出甲乙的划拳统计结果
	printf("%d %d %d\n", va[1], va[0], va[2]);
	printf("%d %d %d\n", vb[1], vb[0], vb[2]);

	vector< pair<char, int> > vm;
	vm.assign(ma.begin(), ma.end());
	// 不知道结构体比较怎么用, 或者说是不是其他标准才行
//	struct {
//		bool operator()(pair<char, int> a, pair<char, int> b) const {
//			return a.second < b.second;
//		}
//	} cmp;
	sort(vm.begin(), vm.end(), cmp);
//	for(int i = 0; i < vm.size(); i++)
//		printf("%c %d\n", vm[i].first, vm[i].second);
	cout << vm[0].first;
	cout << ' ';
	
	vm.assign(mb.begin(), mb.end());
	sort(vm.begin(), vm.end(), cmp);
	cout << vm[0].first;
}
