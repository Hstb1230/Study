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
		// kΪ1ʱ����������, ����Ϊ��id������Ȧ
		// ���ǲ��ܺ��Ը�����, ���Ҫ����
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
			// ��Ϊ id ������0��ͷ, �ᱻ����
			// ����һ������������string
			printf("%05d", id);
			// ����id��������Ȧ(͵������), �����ظ����
			m[id] = true;
		}
	}
	if(!flag) cout << "No one is handsome";

}
