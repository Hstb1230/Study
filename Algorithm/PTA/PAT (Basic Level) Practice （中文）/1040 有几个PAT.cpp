#include <iostream>
using namespace std;

int main() {
	string pat;
	getline(cin, pat);
	int count = 0, tmp = 0, t = 0;
	// �Ӻ���ǰ��T������, ����Aʱ����һ��һ��P����ϵ�����, ������Pʱ�����������
	// ���û����P, ������Aʱֱ�����, �ͻ������ͳ�����(��ΪATǰ�治һ����P)
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
