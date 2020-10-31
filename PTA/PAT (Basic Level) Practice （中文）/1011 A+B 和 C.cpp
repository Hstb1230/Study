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
		if(isMore0(a) != isMore0(b))  // ab���
			flag = (a + b > c);
		else if(isMore0(a) != isMore0(c))  // ac���
		{
			// a��������b������һ������c������
			// a������һ��С��c������
			flag = (a > c);
		}
		else  // abcͬ��
		{
			int d = a - c;
			flag = (d > 0 || b + d > 0);
		}
		printf("Case #%d: %s\n", i, (flag ? "true" : "false"));
    }
}
