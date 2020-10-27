#include <iostream>
#include <cstring>
using namespace std;

const int N = 1010;

int n, m, k;
bool con[N][N], st[N];

void dfs(int u)
{
	st[u] = true;
	for(int i = 1; i <= n; i++)
	{
		if(!st[i] && con[u][i])
			dfs(i);
	}
}

int main()
{
	cin >> n >> m >> k;
	while(m--)
	{
		int x, y;
		cin >> x >> y;
		// ��Ҫע����ǣ����б�Ŵ�1��ʼ
		con[x][y] = con[y][x] = true;
	}
	while(k--)
	{
		int x;
		cin >> x;
		int cnt = 0;  // �޷�����ĳ�������
		/* ����һ��ʼ���г��ж��ǲ���ͨ�ģ���������·���ҳ�������ͨ���Ǽ������� */
		memset(st, 0, sizeof st);
		st[x] = true;
		for(int i = 1; i <= n; i++)
			if(!st[i])
			{
				dfs(i);
				cnt++;
			}
		// ·�������ȳ���������1
		cout << cnt - 1 << endl;
	}
}
