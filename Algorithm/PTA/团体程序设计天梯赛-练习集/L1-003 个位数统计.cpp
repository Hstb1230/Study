#include <iostream>
using namespace std;

int main() {
	// string是c++的字符串类型, 相当于一个不定长的字符数组
	// string s;
	// char是字符类型, 变量名后加[]表示是个数组/指针, 具体长度看题目,
	char s[1001];
	cin >> s;
	// ={0} 相当于把数组的所有元素赋初值
	int time[10] = {0};
	// '\0'相当于整数0,
	// 所以也可以写成 for(int i = 0; s[i]; i++) , 第二个参数就是判断逻辑值, 0/假
	for(int i = 0; s[i] != '\0'; i++) {
		// s[i]是acsii码值, 类似字节集
		// -'0'等于转换成数字
		time[(s[i] - '0')]++;
	}
	for(int i = 0; i < 10; i++) {
		if(time[i] > 0)
			cout << i << ':' << time[i] << endl;
	}
}
