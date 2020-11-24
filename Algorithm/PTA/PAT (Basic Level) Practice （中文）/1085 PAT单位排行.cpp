#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct school
{
	int stuCount;
	int bScore; // 乙级总分
	int aScore; // 甲级总分
	int tScore; // 顶级总分
	int wScore; // 权重总分
};

typedef pair<string, school> mp;

void initSchool(map<string, school> & m, string school)
{
	if(m.count(school) == 0)
	{
		m[school].stuCount
			 = m[school].bScore = m[school].aScore
			 = m[school].tScore = m[school].wScore = 0;
	}
}

void calculateSchool(vector<mp> & v)
{
	for(vector<mp>::iterator it = v.begin(); it != v.end(); it++)
	{
		it->second.wScore = floor(it->second.bScore / 1.5 + it->second.aScore + it->second.tScore * 1.5);
	}
}

void printSchool(vector<mp> & v)
{
	for(vector<mp>::iterator it = v.begin(); it != v.end(); it++)
		printf("%s %d %d\n",
				it->first.c_str(),
				it->second.wScore,
				it->second.stuCount
		);
}

void printSchoolWithRank(vector<mp> & v)
{
	int len = v.size();
	cout << len << endl;
	int lastWeight = 1;
	int lastWeightScore = v[0].second.wScore;
	for(int i = 0; i < len; i++)
	{
		if(v[i].second.wScore != lastWeightScore)
		{
			lastWeight = i + 1;
			lastWeightScore = v[i].second.wScore;
		}
		printf("%d ", lastWeight);
		printf("%s %d %d\n",
				v[i].first.c_str(),
				v[i].second.wScore,
				v[i].second.stuCount
		);
	}
}

bool cmp(mp a, mp b)
{
	if(a.second.wScore != b.second.wScore)
		return a.second.wScore > b.second.wScore;
	else if(a.second.stuCount != b.second.stuCount)
		return a.second.stuCount < b.second.stuCount;
	else
		return a.first < b.first;
}

int main()
{
	int n;
	cin >> n;
	// 准考证号、学校代码
	string id, sCode;
	int score;
	map<string, school> m;
	while(n--)
	{
		cin >> id >> score >> sCode;
		transform(sCode.begin(), sCode.end(), sCode.begin(), ::tolower);
		initSchool(m, sCode);
		m[sCode].stuCount++;
		switch(id[0])
		{
			case 'B':
				m[sCode].bScore += score;
				break;
			case 'A':
				m[sCode].aScore += score;
				break;
			case 'T':
				m[sCode].tScore += score;
				break;
		}
	}
	vector<mp> v(m.begin(), m.end());
	calculateSchool(v);
	sort(v.begin(), v.end(), cmp);
	printSchoolWithRank(v);
}
