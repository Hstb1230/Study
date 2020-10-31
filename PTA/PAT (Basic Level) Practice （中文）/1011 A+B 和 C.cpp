#include <iostream>
using namespace std;

extern bool isMore0(int x)
{
	return !(x >> 31 & 1);
}

int main() {
    int T, a, b, c;
    cin >> T;
    for(int i = 1; i <= T; i++)
    {
        cin >> a >> b >> c;
        if(a > b)
            swap(a, b);
		bool flag;
		if(isMore0(a) != isMore0(b))  // ab异号
			flag = (a + b > c);
		else if(isMore0(a) != isMore0(c))  // ac异号
		{
			// a（正），b（正）一定大于c（负）
			// a（负）一定小于c（正）
			flag = (a > c);
		}
		else  // abc同号
		{
			int d = a - c;
			flag = (d > 0 || b + d > 0);
		}
		printf("Case #%d: %s\n", i, (flag ? "true" : "false"));
    }
}
