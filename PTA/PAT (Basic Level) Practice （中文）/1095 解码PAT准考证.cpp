#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct e
{
	string id;
	int score;
};

bool cmp(e a, e b)
{
	if(a.score == b.score)
		return a.id < b.id;
	return a.score > b.score;
}

bool cmp2(pair<int, int> a, pair<int, int> b)
{
	if(a.second == b.second)
		return a.first < b.first;
	return a.second > b.second;
}

int strToInt(const string & str, int start, int len)
{
	int num = 0;
	for(int i = start; len--; i++)
	{
		num *= 10;
		num += str[i] - '0';
	}
	return num;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<e> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i].id >> v[i].score;
	sort(v.begin(), v.end(), cmp);
	int type;
	bool isNA;
	for(int i = 1; i <= m; i++)
	{
		isNA = true;
		cin >> type;
		printf("Case %d: %d ", i, type);
		switch(type)
		{
			case 1:
			{
				char c;
				cin >> c;
				printf("%c\n", c);
				for(int j = 0; j < n; j++)
				{
					if(v[j].id[0] == c)
					{
						isNA = false;
						printf("%s %d\n", v[j].id.c_str(), v[j].score);
					}
				}
				if(isNA)
				{
					printf("NA\n");
				}
				break;
			}
			case 2:
			{
				string c;
				cin >> c;
				printf("%s\n", c.c_str());
				int sum = 0, count = 0;
				for(int j = 0; j < n; j++)
				{
					if(v[j].id.substr(1, 3) == c)
					{
						isNA = false;
						count++;
						sum += v[j].score;
					}
				}
				if(isNA)
					printf("NA\n");
				else
					printf("%d %d\n", count, sum);
				break;
			}
			case 3:
			{
				string date;
				cin >> date;
				printf("%s\n", date.c_str());
				map<int, int> m;
				for(int j = 0; j < n; j++)
				{
					if(v[j].id.substr(4, 6) == date)
						m[strToInt(v[j].id, 1, 3)] += 1;
				}
				if(m.size() == 0)
					printf("NA\n");
				else
				{
					vector< pair<int, int> > mp(m.begin(), m.end());
					sort(mp.begin(), mp.end(), cmp2);
					int len = mp.size();
					for(int i = 0; i < len; i++)
						printf("%d %d\n", mp[i].first, mp[i].second);
				}
				break;
			}
		}
	}
}
