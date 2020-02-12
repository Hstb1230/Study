#include <iostream>
using namespace std;

void countChar(string s, int chars[]) {
	// 因为不区分大小写, 所以只需要26个数组大小
	// 之前想着用map也是因为理解错题意
	for(int i = s.length() - 1; i >= 0; i--) {
		// 首先得是个字母
		// Firstly, it musts be a letter
		if(isalpha(s[i]))
			// 将acsii码转换为相对a的偏移量
			// convert ascii code to position location to 'a'
			chars[tolower(s[i]) - 'a']++;
	}
}

// 调试(debug)
void printChars(const int * chars) {
	for(int i = 0; i < 26; i++) {
		if(chars[i] > 0) {
			printf("%c: %d\n", 'a' + i, chars[i]);
		}
	}
}

// 查找最大值的下标
// find the index of max value
int findMax(const int * chars) {
	int max = 0;
	for(int i = 0; i < 26; i++) {
		// 只处理更大值的情况,
		// 也就满足使用更小字母序的条件
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
	// 最大值的下标是相对于字母A而言的
	// The index of maximum is relative to the letter a.
	printf("%c %d", 'a' + max, chars[max]);
}
