#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;

int n, m, k, cnt;
queue<int> q[25];  // �����20������
int fin[1010], beg[1010];  // �����1000���ͻ�

int main()
{
	cin >> n >> m >> k >> cnt;
	for(int i = 1; i <= k; i++)  // ��Ŵ�1��ʼ
	{
		int t;
		cin >> t;
		// ����̵��Ŷ�·�ߣ��������ٵ��Ǹ����ڣ�
		int fast = 0;
		for(int w = 1; w < n; w++)
			if(q[w].size() < q[fast].size())
				fast = w;

		if(q[fast].size() >= m)  // ���д��ڶ������ˣ��ҳ����ȷ�����ɵĴ���
			for(int w = 1; w < n; w++)
				if(q[w].front() < q[fast].front())
					fast = w;

		beg[i] = (q[fast].size() ? q[fast].back() : 0);  // ��ʼʱ��Ϊ��һλ�Ľ���ʱ��
		if(q[fast].size() >= m)  // �õ���ʼʱ�����ܳ���
			q[fast].pop();
		// �������ʱ��
		fin[i] = beg[i] + t;
		q[fast].push(fin[i]);
	}
	while(cnt--)
	{
		int x;
		cin >> x;
		// ��ʼʱ�䲻����17�㣬�����ǽ���ʱ��
		if(beg[x] >= 540)
			puts("Sorry");
		else
			printf("%02d:%02d\n", (8 + fin[x] / 60), (fin[x] % 60));
	}
}
