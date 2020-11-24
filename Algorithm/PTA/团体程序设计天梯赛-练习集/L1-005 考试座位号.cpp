#include <iostream>
#include <cstring>
// C++的数组库, 可以扩展数组(动态数组)
#include <vector>
using namespace std;

typedef struct tester {
	// 改成string类型, 可以直接赋值
	string id;
	// char id[17];    // 准考证号
	int exam_id;       // 考试座位号
} retester;
/*
struct [type_name] {
	member_type member_name;
} [variable_name];
*/
/*
C++
typedef member_type type_name
typedef struct [type_name] {
	member_type member_name;
} type_rename;
*/

// 声明一个一维整数动态数组 int[]
vector<int> vi;
// 声明一个二维整数动态数组 int [][]
// vector<vector<int>> vii;
// >> 会被当做 cin >> i 的 >>, 所以报错
vector< vector<int> > vii;
// 解决办法是这样, 但是有点麻烦, 一不小心就写错,
// 特别是写三维以上的时候, 看起来就很丑
// 所以把一维数组重命名(随便命名)
typedef vector<int> int_single_array;
vector<int_single_array> int_two_array;

int main() {
	retester rt;
	int n;
	cin >> n;
	// 因为调试要用, 所以先用个变量记录下n
	int copy_n = n;
	tester t[n + 1];    // 用数组索引当做试机座位号, 范围为 1~N, 所以需要加1
	int test_id;        // 记录试机座位号
	// 因为后面用不到n, 所以可以直接拿来当输入数据的计数器
	while(n--) {
		// 因为一开始不能确定座位号码, 所以需要单独的变量记录,
        // 而t[0]刚好用不上, 就拿来开坑
		cin >> t[0].id >> test_id >> t[0].exam_id;
		// strcpy(t[test_id].id, t[0].id);
		// string类型可以直接赋值
		t[test_id].id = t[0].id;
		t[test_id].exam_id = t[0].exam_id;
	}
	n = copy_n;
	for(int i = 1; i <= n; i++) {
		// 但是用printf输出麻烦, 需要调用c_str方法转换成字符数组
		//printf("%s %d %d\n", t[i].id.c_str(), i, t[i].exam_id);
	}
	// 回归题目本身
	// 已经得到考生信息, 这时候开始查询
	cin >> n;
	while(n--) {
		cin >> test_id;
		printf("%s %d\n", t[test_id].id.c_str(), t[test_id].exam_id);
	}
}
