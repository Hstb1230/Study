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
		// 需要注意的是，城市编号从1开始
		con[x][y] = con[y][x] = true;
	}
	while(k--)
	{
		int x;
		cin >> x;
		int cnt = 0;  // 无法到达的城市数量
		/* 假设一开始所有城市都是不连通的，深搜所有路线找出还能联通的那几个城市 */
		memset(st, 0, sizeof st);
		st[x] = true;
		for(int i = 1; i <= n; i++)
			if(!st[i])
			{
				dfs(i);
				cnt++;
			}
		// 路线数量比城市数量少1
		cout << cnt - 1 << endl;
	}
}
