#include <iostream>
using namespace std;

int main() {
	// n - 字符个数, c - 输出的字符
	int n;
	char c;
	cin >> n >> c;
	// line - 行数, 只包含上半部分
	// remain - 多余未输出的字符数量
	int line = 0;
	int remain = 0;
	// 计算行数line
	if(n > 0) {
		// 方法: 判断剩余字符数remain能否满足第line行所需要的字符数量
        // 不能就是最终的剩余字符数, 否则line自增, 继续进行该过程
		// 因为每次要减去两倍字符数量, 会和1个字符那行(只需要一个)冲突, 所以初始化line并忽略这行
		line = 1;
		remain = n - 1;
		while(remain > 2 * (2 * line + 1)) {
			remain -= 2 * (2 * line + 1);
			line++;
		}
	}
	// cout << line << ' ' << remain << endl;
	// 输出上半部分(倒金字塔)
	for(int i = line; i > 0; i--) {
		// 先输出空格,
		// 空格数 = 总行数line - 当前行倒数i
		for(int j = i; j < line; j++)
			cout << ' ';
        // 输出字符,
		// 因为不能一次性输出重复文本, 所以借助循环
        // 字符数 = 2 * i - 1
		for(int j = 2 * i - 1; j > 0; j--)
			cout << c;
        // 每行结尾换一行
		cout << endl;
	}
	// 输出下半部分(正三角)
	// 因为不能输出第一行, 所以从2开始
	for(int i = 2; i <= line; i++) {
		for(int j = i; j < line; j++)
			cout << ' ';
		for(int j = 2 * i - 1; j > 0; j--)
			cout << c;
		cout << endl;
	}
	cout << remain << endl;
}
