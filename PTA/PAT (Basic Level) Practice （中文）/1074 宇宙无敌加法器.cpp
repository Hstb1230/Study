#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void string_to_int(vector<int> & array, bool zero_to_ten = false)
{
	int len = array.size();
	for(int i = 0; i < len; i++) {
		array[i] -= '0';
		if(array[i] == 0 && zero_to_ten)
			array[i] = 10;
	}
}

void print_array(vector<int> array)
{
	int len = array.size();
	for(int i = 0; i < len; i++) {
		printf("%d", array[i]);
	}
	cout << endl;
}

int main() {
	string str_base, str_a, str_b;
	cin >> str_base >> str_a >> str_b;
	vector<int> base(str_base.rbegin(), str_base.rend()),
				a(str_a.rbegin(), str_a.rend()),
				b(str_b.rbegin(), str_b.rend());
	string_to_int(base, true), string_to_int(a), string_to_int(b);
//	print_array(base), print_array(a), print_array(b);
	// 保证b是最小的
	if(b.size() > a.size())
		a.swap(b);
	vector<int> ret(a);
	for(int i = 0; i < ret.size(); i++) {
		if(i < b.size())
			ret[i] += b[i];
		if(i >= base.size())
			base.insert(base.end(), 2, 10);
		if(ret[i] >= base[i])
		{
			if(i + 1 >= ret.size())
				ret.insert(ret.end(), 2, 0);
			ret[i + 1] += ret[i] / base[i];
			ret[i] = ret[i] % base[i];
		}
//		print_array(ret);
	}
	reverse(ret.begin(), ret.end());
	// 删除开头的0
	int loc = 0;
	while(loc + 1 < ret.size() && ret[loc] == 0)
		loc++;
	if(loc > 0)
		ret.erase(ret.begin(), ret.begin() + loc);
	print_array(ret);
}
