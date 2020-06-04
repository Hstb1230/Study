#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> m(n + 1);
	for(int i = 1; i <= n; i++)
		cin >> m[i];
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			// 假设 i 、 j 是狼
			// role 是假设的玩家角色
			vector<int> role(n + 1, 1), lie(0);
			role[i] = role[j] = -1;
			for(int k = 1; k <= n; k++)
			{
				/*
					v[k] < 0 , role[abs(v[k])] < 0
					v[k] < 0 , role[abs(v[k])] > 0
					v[k] > 0 , role[abs(v[k])] < 0
					v[k] > 0 , role[abs(v[k])] > 0
				*/
				if(m[k] * role[abs(m[k])] < 0)
					// 说明k说谎
					lie.push_back(k);
			}
			if(lie.size() == 2 && (role[lie[0]] + role[lie[1]]) == 0)
			{
				printf("%d %d", i, j);
				return 0;
			}
		}
	}
	printf("No Solution");
	return 0;
}
