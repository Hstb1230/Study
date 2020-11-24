#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int count_sum(string s) {
	int len = s.length();
	int sum = 0;
	for(int i = 0; i < len; i++) {
		sum += s[i] - '0';
	}
	return sum;
}

void print_vector(const vector<int> & v) {
	int len = v.size();
	for(int i = 0; i < len; i++) {
		if(i > 0) printf(" ");
		printf("%d", v[i]);
	}
	printf("\n");
}

int main() {
	int n;
	cin >> n;
	string s;
	vector<int> v;
	for(int i = 0; i < n; i++) {
		cin >> s;
		v.push_back(count_sum(s));
	}
	sort(v.begin(), v.end());
	vector<int>::iterator it = unique(v.begin(), v.end());
	v.erase(it, v.end());
	cout << v.size() << endl;
	print_vector(v);
}
