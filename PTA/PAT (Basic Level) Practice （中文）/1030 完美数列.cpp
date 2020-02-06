#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	// ������long long��....
	long long n, p;
	cin >> n >> p;
	vector<long long> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	int min = 0, max = 0;
	long long mp, j = 0;
	// ��ͷ��ʼ, �������Ե�ǰ��㿪ʼ���������
	// ��Ϊ��������, ������һ�����е�mpֵһ������(�������),
	// ���, ��һ�����е�һ��������һ������, ��һ�β���Ҫ������ٿ�ʼ
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
