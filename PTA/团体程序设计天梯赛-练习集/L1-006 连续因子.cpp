#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	
    // �趨�յ�, ��Ϊ����е�����һ�����ᳬ����ƽ����(�е���)
	int tDest = sqrt(n) + 1;    // ��1��Ϊ��ѭ������д��������
	// ��ʾ�۳� �� ��ʱ���е��յ�
	int cum, tEnd;
	// ��ʾ��������������е���� �� �յ�
	int start, end;
	end = start = n;
	
	for(int tStart = 2; tStart < tDest; tStart++) {
		// �ж��Ƿ���������
		if(n % tStart != 0) continue;
		
		cum = tEnd = tStart;
		
		do {
			cum *= ++tEnd;
		} while(n % cum == 0);
		// �����ʱ���и���, ������Ϊ��������
		if(tEnd - tStart > end - start) {
			end = tEnd;
			start = tStart;
		}
	}
	if(end - start == 0) end++;
	cout << end - start << endl;
	cout << start;
	for(int i = start + 1; i < end; i++) {
		cout << '*' << i;
	}
	
}
