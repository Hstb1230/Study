#include <iostream>
#include <vector>
using namespace std;

vector<int> tree[100];
int dp[100] = { 0 }, max_deep = 0;

void dfs(int cur, int deep)
{
	if(tree[cur].size() == 0)
	{
		dp[deep]++;
		if(deep > max_deep)
			max_deep = deep;
		return;
	}
	for(int i = tree[cur].size() - 1; i >= 0; i--)
		dfs(tree[cur][i], deep + 1);
}

int main()
{
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++)
	{
		int root, k, t;
		cin >> root >> k;
		while(k-- > 0)
		{
			cin >> t;
			tree[root].push_back(t);
		}
	}
	dfs(1, 0);
	cout << dp[0];
	for(int i = 1; i <= max_deep; i++)
		printf(" %d", dp[i]);
}
