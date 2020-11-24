#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct e
{
	string t;
	int value;
};

bool cmp(e & a, e & b)
{
	return a.value != b.value ? a.value > b.value : a.t < b.t;
}

int main()
{
	int n, m, type;
	cin >> n >> m;

	vector<e> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i].t >> v[i].value;
	sort(v.begin(), v.end(), cmp);

	for(int i = 1; i <= m; i++)
	{
		string param;
		cin >> type >> param;
		printf("Case %d: %d %s\n", i, type, param.c_str());

		vector<e> ans;
		int sum = 0, cnt = 0;
		if(type == 1)
		{
			for(int j = 0; j < n; j++)
			{
				if(v[j].t[0] == param[0])
					ans.push_back({ v[j].t, v[j].value });
			}
		}
		else if(type == 2)
		{
			for(int j = 0; j < n; j++)
			{
				if(v[j].t.substr(1, 3) == param)
				{
					cnt++;
					sum += v[j].value;
				}
			}
			if(cnt > 0)
				printf("%d %d\n", cnt, sum);
		}
		else if(type == 3)
		{
			unordered_map<string, int> m;
			for(int j = 0; j < n; j++)
			{
				if(v[j].t.substr(4, 6) == param)
					m[v[j].t.substr(1, 3)] += 1;
			}
			for(auto it : m)
				ans.push_back({ it.first, it.second });
		}
		sort(ans.begin(), ans.end(), cmp);
		for(auto it : ans)
			printf("%s %d\n", it.t.c_str(), it.value);
		if((ans.size() == 0 && type != 2) || (type == 2 && cnt == 0))
			printf("NA\n");
	}
}
