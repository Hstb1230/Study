#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

const int inf = 99999999;

int ap[501][501];
int r[501] = {0};

map<int,int> mp;
int minPath = inf;
int maxRes = 0;

bool v[501] = {false};

void cal(int cur, int to, int res, int path)
{
	v[cur] = true;
	res += r[cur];
	if(cur == to)
	{
		mp[path] += 1;
		if(path < minPath)
		{
			minPath = path;
			maxRes = res;
		}
		else if(path == minPath && res > maxRes)
		{
			minPath = path;
			maxRes = res;
		}
		return;
	}
	for(int i = 0; i < 501; i++)
	{
		if(ap[cur][i] == inf) continue;
		if(v[i]) continue;
		cal(i, to, res, path + ap[cur][i]);
		v[i] = false;
	}
}

int main()
{
	fill(ap[0], ap[0] + 501 * 501, inf);
	int n, m, from, to;
	cin >> n >> m >> from >> to;
	for(int i = 0; i < n; i++)
		cin >> r[i];
	int tFrom, tTo, tLen;
	for(int i = 0; i < m; i++)
	{
		cin >> tFrom >> tTo >> tLen;
		ap[tFrom][tTo] = ap[tTo][tFrom] = tLen;
	}
	cal(from, to, 0, 0);
	cout << mp[minPath] << " " << maxRes;
}
