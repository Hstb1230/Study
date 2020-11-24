#include <iostream>
using namespace std;

void countChar(string s, int chars[]) {
	// ��Ϊ�����ִ�Сд, ����ֻ��Ҫ26�������С
	// ֮ǰ������mapҲ����Ϊ��������
	for(int i = s.length() - 1; i >= 0; i--) {
		// ���ȵ��Ǹ���ĸ
		// Firstly, it musts be a letter
		if(isalpha(s[i]))
			// ��acsii��ת��Ϊ���a��ƫ����
			// convert ascii code to position location to 'a'
			chars[tolower(s[i]) - 'a']++;
	}
}

// ����(debug)
void printChars(const int * chars) {
	for(int i = 0; i < 26; i++) {
		if(chars[i] > 0) {
			printf("%c: %d\n", 'a' + i, chars[i]);
		}
	}
}

// �������ֵ���±�
// find the index of max value
int findMax(const int * chars) {
	int max = 0;
	for(int i = 0; i < 26; i++) {
		// ֻ�������ֵ�����,
		// Ҳ������ʹ�ø�С��ĸ�������
		// it only handles larger value,
		// and also satisfies the condition of using smaller alphabetical order
		if(chars[i] > chars[max])
			max = i;
	}
	return max;
}

int main() {
	string s;
	getline(cin, s);
	int chars[26] = {0};
	countChar(s, chars);
//	printChars(chars);
	int max = findMax(chars);
	// ���ֵ���±����������ĸA���Ե�
	// The index of maximum is relative to the letter a.
	printf("%c %d", 'a' + max, chars[max]);
}
