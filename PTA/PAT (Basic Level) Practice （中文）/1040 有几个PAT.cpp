#include <iostream>
using namespace std;

int main() {
	string pat;
	getline(cin, pat);
	int count = 0, tmp = 0, t = 0;
	// 从后往前数T的数量, 遇到A时计算一次一个P能组合的数量, 等遇到P时再增加组合数
	// 如果没遇到P, 在遇到A时直接添加, 就会出现误统计情况(因为AT前面不一定有P)
	for(int i = pat.length(); i-- != 0; ) {
		switch(pat[i]) {
			case 'T':
				++t;
				break;
			case 'A':
				tmp += t;
				break;
			case 'P':
				count += tmp;
				count %= 1000000007;
				break;
		}
	}
	cout << count;
	return 0;
}
