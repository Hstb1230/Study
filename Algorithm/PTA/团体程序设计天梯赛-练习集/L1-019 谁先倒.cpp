#include <iostream>
using namespace std;

int main() {
	// �׵ľ���  �ҵľ���
	int ac, bc;
	cin >> ac >> bc;
	int n;
	cin >> n;
	int au, bu;
	au = bu = 0;
	while(n--) {
		// �׺� �ײ� �Һ� �Ҳ�
		int ai, ag, bi, bg;
		cin >> ai >> ag >> bi >> bg;
		if(ag == ai + bi && bg == ai + bi) continue;
		if(ag != ai + bi && bg != ai + bi) continue;
		if(ag == ai + bi) au++;
		if(bg == ai + bi) bu++;
		if(au > ac || bu > bc) break;
	}
	if(au > ac) {
		cout << 'A' << endl;
		cout << bu << endl;
	} else if(bu > bc) {
		cout << 'B' << endl;
		cout << au << endl;
	}
}
