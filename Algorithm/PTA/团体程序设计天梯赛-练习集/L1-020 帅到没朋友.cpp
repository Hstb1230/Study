#include <iostream>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;
	map<int, bool> m;
	string s;
	while(n--) {
		int k;
		cin >> k;
		// k为1时等于自恋狂, 不认为该id在朋友圈
		// 但是不能忽略该数据, 因此要读完
		if(k == 1) {
			getline(cin, s);
			continue;
		}
		while(k--) {
			int id;
			cin >> id;
			m[id] = true;
		}
	}
	cin >> n;
	int flag = 0;
	while(n--) {
		int id;
		cin >> id;
		if(m.count(id) == 0) {
			if(++flag > 1) cout << ' ';
			// 因为 id 可能是0开头, 会被忽略
			// 还有一个方法就是用string
			printf("%05d", id);
			// 将该id加入朋友圈(偷懒做法), 避免重复输出
			m[id] = true;
		}
	}
	if(!flag) cout << "No one is handsome";

}
