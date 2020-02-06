#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	string id;
	int de;
	int cai;
	int total;
	int type;
} tester;

bool cmp(tester t1, tester t2) {
	if(t1.type != t2.type)
		return t1.type < t2.type;
	if(t1.total != t2.total)
		return t1.total > t2.total;
	if(t1.de != t2.de)
		return t1.de > t2.de;
	return t1.id < t2.id;
}

int main() {
	int n;
	int l, h;
	cin >> n >> l >> h;
	vector<tester> t;
	tester tmp;
	while(n--) {
		cin >> tmp.id >> tmp.de >> tmp.cai;
		tmp.total = tmp.de + tmp.cai;
		if(tmp.de < l || tmp.cai < l)
			// 未达线, 无录取资格
			continue;
		else if(tmp.de >= h && tmp.cai >= h)
			// 才德尽全
			tmp.type = 1;
		else if(tmp.de >= h && tmp.cai < h)
		    // 德胜才
			tmp.type = 2;
		else if(tmp.de >= tmp.cai && tmp.de < h && tmp.cai < h)
			// 才德兼亡 but 德胜才
			tmp.type = 3;
		else
			tmp.type = 4;
		t.push_back(tmp);
	}
	sort(t.begin(), t.end(), cmp);
	cout << t.size() << endl;
	for(int i = 0; i < t.size(); i++) {
		printf("%s %d %d\n", t[i].id.c_str(), t[i].de, t[i].cai);
	}
}
