#include <iostream>
using namespace std;

int main() {
	// n - �ַ�����, c - ������ַ�
	int n;
	char c;
	cin >> n >> c;
	// line - ����, ֻ�����ϰ벿��
	// remain - ����δ������ַ�����
	int line = 0;
	int remain = 0;
	// ��������line
	if(n > 0) {
		// ����: �ж�ʣ���ַ���remain�ܷ������line������Ҫ���ַ�����
        // ���ܾ������յ�ʣ���ַ���, ����line����, �������иù���
		// ��Ϊÿ��Ҫ��ȥ�����ַ�����, ���1���ַ�����(ֻ��Ҫһ��)��ͻ, ���Գ�ʼ��line����������
		line = 1;
		remain = n - 1;
		while(remain > 2 * (2 * line + 1)) {
			remain -= 2 * (2 * line + 1);
			line++;
		}
	}
	// cout << line << ' ' << remain << endl;
	// ����ϰ벿��(��������)
	for(int i = line; i > 0; i--) {
		// ������ո�,
		// �ո��� = ������line - ��ǰ�е���i
		for(int j = i; j < line; j++)
			cout << ' ';
        // ����ַ�,
		// ��Ϊ����һ��������ظ��ı�, ���Խ���ѭ��
        // �ַ��� = 2 * i - 1
		for(int j = 2 * i - 1; j > 0; j--)
			cout << c;
        // ÿ�н�β��һ��
		cout << endl;
	}
	// ����°벿��(������)
	// ��Ϊ���������һ��, ���Դ�2��ʼ
	for(int i = 2; i <= line; i++) {
		for(int j = i; j < line; j++)
			cout << ' ';
		for(int j = 2 * i - 1; j > 0; j--)
			cout << c;
		cout << endl;
	}
	cout << remain << endl;
}
