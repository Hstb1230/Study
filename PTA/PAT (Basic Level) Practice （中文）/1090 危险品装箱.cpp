#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	map<int, vector<int> > ms;
	int a, b;
	for(int i = 0; i < n; i++)
	{
		cin >> a >> b;
		ms[a].push_back(b);
		ms[b].push_back(a);
	}

	int k, g;
	while(m--)
	{
		cin >> k;
		map<int, int> v;
		while(k--)
		{
			cin >> g;
			if(ms.count(g) == 0)
				continue;
			v[g] = 1;
		}
		bool vaild = true;
		for(map<int, int>::iterator it = v.begin(); it != v.end(); it++)
		{
			for(int i = 0; i < ms[it->first].size(); i++)
			{
				if(v.count(ms[it->first][i]) > 0)
				{
					vaild = false;
					break;
				}
			}
			if(!vaild)
				break;
		}
		if(vaild)
			printf("Yes\n");
		else
			printf("No\n");
	}

}
