#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	string name;
	string id;
	int score;
} student;

bool cmp(student s1, student s2) {
	return s1.score < s2.score;
}

int main() {
	int n;
	cin >> n;
	vector<student> s(n);
	for(int i = 0; i < n; i++) {
		cin >> s[i].name >> s[i].id >> s[i].score;
	}
	sort(s.begin(), s.end(), cmp);
	cout << s[n - 1].name << ' ' << s[n - 1].id << endl;
	cout << s[0].name << ' ' << s[0].id << endl;
	
}
