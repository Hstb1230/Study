#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<int, int> m;

vector<int> key;

void createMap(const int start) {
	if(m.count(start) > 0) return;
	int next;
	if(start % 2 == 1) {
		next = (3 * start + 1) / 2;
	} else {
		next = start / 2;
	}
	m[start] = next;
	if(next == 1) return;
	if(m.count(next) > 0) return;
	return createMap(next);
}

void printMap(const int start) {
	cout << start;
	if(start == 1) {
		cout << endl;
		return;
	}
	cout << " -> ";
	printMap(m[start]);
}

bool searchMap(const int start, const int toFind) {
	if(m[start] == 1) return false;
	if(m[start] == toFind) return true;
	return searchMap(m[start], toFind);
}

void updateKey(const int newKey) {
	key.push_back(newKey);
	// -1是因为要忽略新key, 否则重复遍历
	for(int i = 0; i < key.size() - 1; i++) {
		if(searchMap(newKey, key[i])) {
			key.erase(key.begin() + i);
			i--;
		}
	}
}

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	int n;
	cin >> n;
	int input;
	while(n--) {
		cin >> input;
		// 判断路径中是否已存在节点
		// 存在则无需重复创建路径, 也说明不是关键点
		if(m.count(input)) continue;
		createMap(input);
		
		updateKey(input);
		
		// printMap(input);
	}
	sort(key.begin(), key.end(), cmp);
	int flag = 0;
	for(int i = 0; i < key.size(); i++) {
		if(flag++) cout << ' ';
		cout << key[i];
	}
}
