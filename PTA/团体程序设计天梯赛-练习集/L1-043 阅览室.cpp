#include <iostream>
#include <map>
using namespace std;

map<int, int> borrows;

int main() {
	int n;  // 天数
	cin >> n;
	int book_id;
	char opt;
	int hour, minute;
	// 容易漏的一个点:
	// 一天内可能有多个读者借同一本书,
	// 所以不能等最后再计算借阅情况
	int reader = 0;
	int time = 0;
	while(n) {
		scanf("%d %c %d:%d", &book_id, &opt, &hour, &minute);
		if(book_id == 0) {
			// 一天结束
			if(time == 0)
				printf("%d %d\n", reader, 0);
			else
				printf("%d %d\n", reader, int(time * 1.0 / reader + 0.5f));
			n--;
			borrows.clear();
			time = reader = 0;
		} else if(opt == 'E' && borrows.count(book_id)) {
			// 归还图书
			reader++;
			time += hour * 60 + minute - borrows[book_id];
			borrows.erase(book_id);
		} else if(opt == 'S') {
			borrows[book_id] = hour * 60 + minute;
		}
	}
}
