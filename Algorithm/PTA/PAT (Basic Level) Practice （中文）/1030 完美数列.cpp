#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	// 尽量用long long吧....
	long long n, p;
	cin >> n >> p;
	vector<long long> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	int min = 0, max = 0;
	long long mp, j = 0;
	// 从头开始, 往后找以当前起点开始的最大数列
	// 因为升序排序, 所以下一个数列的mp值一定更大(或者相等),
	// 因此, 下一个数列的一定包含上一个数列, 下一次不需要从起点再开始
	for(int i = 0; i < n; i++) {
		mp = v[i] * p;
		for(; j < n; j++) {
			if(v[j] > mp) break;
		}
//		printf("%d %d\n", i, j);
		if(j - i > max - min) {
			max = j;
			min = i;
		}
		if(j == n - 1) break;
	}
	cout << max - min;
}
