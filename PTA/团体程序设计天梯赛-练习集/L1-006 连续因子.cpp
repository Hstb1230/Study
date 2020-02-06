#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	
    // 设定终点, 因为最长序列的因子一定不会超过其平方根(有点绕)
	int tDest = sqrt(n) + 1;    // ＋1是为了循环条件写起来方便
	// 表示累成 与 临时序列的终点
	int cum, tEnd;
	// 表示符合条件的最长序列的起点 与 终点
	int start, end;
	end = start = n;
	
	for(int tStart = 2; tStart < tDest; tStart++) {
		// 判断是否属于因子
		if(n % tStart != 0) continue;
		
		cum = tEnd = tStart;
		
		do {
			cum *= ++tEnd;
		} while(n % cum == 0);
		// 如果临时序列更长, 就设置为最终序列
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
