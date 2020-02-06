#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	int value;
	int next;
} node;

int main() {
	int begin, n, k, address;
	cin >> begin >> n >> k;
	map<int, node> m;
	for(int i = 0; i < n; i++) {
		cin >> address;
		cin >> m[address].value >> m[address].next;
	}
	vector<int> v(n);
	address = begin;
	int sum = 0;
	for(int i = 0; i < n; i++) {
		if(address == -1) break;
		sum++;
		v[i] = address;
		address = m[address].next;
	}
	
	for(int i = 0; i < (sum - sum % k); i += k)
		reverse(v.begin() + i, v.begin() + i + k);

	for(int i = 0; i < sum - 1; i++) {
		printf("%05d %d %05d\n", v[i], m[v[i]].value, v[i + 1]);
	}
	if(sum > 0)
		printf("%05d %d -1\n", v[sum - 1], m[v[sum - 1]].value);
	else
		printf("%05d %d -1\n", 0, m[0].value);

}
