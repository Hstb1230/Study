#include <iostream>
#include <cmath>
using namespace std;

int cntA[3], cntB[3];  // ʤƽ������
int winA[3], winB[3];  // ʤ������ͳ��
const string str = "CJB";

extern int c2i(char c)
{
	return str.find(c);
}

extern char best(const int * win)
{
	int m = 0;
	for(int i = 1; i < 3; i++)
	{
		if(win[i] > win[m] || (win[i] == win[m] && str[i] < str[m]))
			m = i;
	}
	return str[m];
}

int main()
{
	int n;
	cin >> n;
	char a, b;
	while(n--)
	{
		cin >> a >> b;
		int x = c2i(a), y = c2i(b);  // ����
		int rA = 0, rB = 0;  // Ĭ��ƽ��
		if(abs(x - y) == 1)
		    rA = (x < y ? 1 : -1), rB = -rA;
		else if(abs(x - y) == 2)
		    rA = (x > y ? 1 : -1), rB = -rA;
        rA++, rB++; // ��0��ƽ1��ʤ2
		cntA[rA]++, cntB[rB]++;
		if(rA == 2)
			winA[x]++;
		else if(rB == 2)
			winB[y]++;
	}
	printf("%d %d %d\n", cntA[2], cntA[1], cntA[0]);
	printf("%d %d %d\n", cntB[2], cntB[1], cntB[0]);
	printf("%c %c", best(winA), best(winB));
}
