#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;

int n, m, k, cnt;
queue<int> q[25];  // 最多有20个窗口
int fin[1010], beg[1010];  // 最多有1000个客户

int main()
{
	cin >> n >> m >> k >> cnt;
	for(int i = 1; i <= k; i++)  // 编号从1开始
	{
		int t;
		cin >> t;
		// 找最短的排队路线（即人最少的那个窗口）
		int fast = 0;
		for(int w = 1; w < n; w++)
			if(q[w].size() < q[fast].size())
				fast = w;

		if(q[fast].size() >= m)  // 所有窗口都排满了，找出最先服务完成的窗口
			for(int w = 1; w < n; w++)
				if(q[w].front() < q[fast].front())
					fast = w;

		beg[i] = (q[fast].size() ? q[fast].back() : 0);  // 开始时间为上一位的结束时间
		if(q[fast].size() >= m)  // 拿到开始时间后才能出队
			q[fast].pop();
		// 保存结束时间
		fin[i] = beg[i] + t;
		q[fast].push(fin[i]);
	}
	while(cnt--)
	{
		int x;
		cin >> x;
		// 开始时间不晚于17点，而不是结束时间
		if(beg[x] >= 540)
			puts("Sorry");
		else
			printf("%02d:%02d\n", (8 + fin[x] / 60), (fin[x] % 60));
	}
}
