#include <iostream>
using namespace std;
// �������
// ģ���������
// ������ʱ, һ��ֻ����������, ���Գ�������һС����,
// ����ÿ��ʣ�µ�����, �����ͷ�����Ǳ�����(��x10)
// ��֮���ԣ�1, ����Ϊ��������11111...111
int main() {
	int s = 0;
	int x, n = 0;
	cin >> x;
	while(s < x) {
		n++;
		s *= 10;
		s += 1;
	}
	while(true) {
		cout << (int)(s / x);
		s %= x;
		if(s == 0) break;
		s *= 10;
		s += 1;
		n++;
	}
	cout << ' ' << n;
}
