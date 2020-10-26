#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

struct Student
{
	int c, m, e, avg;
	int rank, best;
};

typedef pair<int, Student> PIS;
map<int, Student> mScore;
vector<PIS> aScore;

int diff = 4;

const char * T = "ACME";

bool cmp(PIS a, PIS b)
{
	int x[4] = { a.second.avg, a.second.c, a.second.m, a.second.e };
	int y[4] = { b.second.avg, b.second.c, b.second.m, b.second.e };
	return x[diff] > y[diff];
}

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	while(N--)
	{
		int id, c, m, e;
		scanf("%d%d%d%d", &id, &c, &m, &e);
		int avg = (c + m + e);
		mScore[id] = { c, m, e, avg, 0, 0 };
	}

	aScore.assign(mScore.begin(), mScore.end());
	
 	while(diff--)
	{
		sort(aScore.begin(), aScore.end(), cmp);
		int rank = 0, lastScore = 0;
		for(int j = 0; j < aScore.size(); j++)
		{
			Student * s = &(aScore[j].second);
			int x[] = { s->avg, s->c, s->m, s->e };
			if(lastScore != x[diff])
			{
				rank = j + 1;
				lastScore = x[diff];
			}
			if(rank <= s->rank || s->rank == 0)
				s->rank = rank, s->best = diff;
		}
	}

	for(auto s : aScore)
		mScore[s.first] = s.second;

	while(M--)
	{
		int id;
		scanf("%d", &id);
		if(mScore.count(id) == 0)
			puts("N/A");
		else
			printf("%d %c\n", mScore[id].rank, T[mScore[id].best]);
	}
}

