#include <iostream>
using namespace std;

int main() {
	// string��c++���ַ�������, �൱��һ�����������ַ�����
	// string s;
	// char���ַ�����, ���������[]��ʾ�Ǹ�����/ָ��, ���峤�ȿ���Ŀ,
	char s[1001];
	cin >> s;
	// ={0} �൱�ڰ����������Ԫ�ظ���ֵ
	int time[10] = {0};
	// '\0'�൱������0,
	// ����Ҳ����д�� for(int i = 0; s[i]; i++) , �ڶ������������ж��߼�ֵ, 0/��
	for(int i = 0; s[i] != '\0'; i++) {
		// s[i]��acsii��ֵ, �����ֽڼ�
		// -'0'����ת��������
		time[(s[i] - '0')]++;
	}
	for(int i = 0; i < 10; i++) {
		if(time[i] > 0)
			cout << i << ':' << time[i] << endl;
	}
}
