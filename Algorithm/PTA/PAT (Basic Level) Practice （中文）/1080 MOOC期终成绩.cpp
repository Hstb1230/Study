#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct scoreInfo
{
	int code;   // ���߱��
	int mid;    // ����
	int final;  // ��ĩ
	int generate; // ���ճɼ�
};

typedef pair<string, scoreInfo> mp;

void generateStu(map<string, scoreInfo> & m, string name)
{
	if(m.count(name) == 0)
	{
		m[name].code = m[name].mid = m[name].final = -1;
	}
}

bool cmp(mp a, mp b)
{
	if(a.second.generate == b.second.generate)
		// ��ѧ��
		return a.first < b.first;
	else
		return a.second.generate > b.second.generate;
}

void calculateScore(vector<mp> & stuList)
{
	int len = stuList.size();
	for(int i = 0; i < len; i++)
	{
		if(stuList[i].second.mid < stuList[i].second.final)
			stuList[i].second.generate = stuList[i].second.final;
		else
			stuList[i].second.generate = int(0.4 * stuList[i].second.mid + 0.6 * stuList[i].second.final + 0.5);
	}
}

void printStuList(vector<mp> stuList)
{
//	printf("\n");
	int len = stuList.size();
	for(int i = 0; i < len; i++)
	{
		if(stuList[i].second.code < 200 || stuList[i].second.generate < 60) continue;
		printf("%s %d %d %d %d\n",
			stuList[i].first.c_str(),
			stuList[i].second.code,
			stuList[i].second.mid,
			stuList[i].second.final,
			stuList[i].second.generate
		);
	}
}

int main()
{
//	 P���������߱����ҵ��ѧ��������M���μ������п��Ե�ѧ��������N���μ�����ĩ���Ե�ѧ������
	int P, M, N;
	cin >> P >> M >> N;
	string id;
	int score;
	map<string, scoreInfo> m;
	for(int i = 0; i < P; i++)
	{
		cin >> id >> score;
		generateStu(m, id);
		m[id].code = score;
	}
	for(int i = 0; i < M; i++)
	{
		cin >> id >> score;
		generateStu(m, id);
		m[id].mid = score;
	}
	for(int i = 0; i < N; i++)
	{
		cin >> id >> score;
		generateStu(m, id);
		m[id].final = score;
	}
	vector<mp> stuList(m.begin(), m.end());
	calculateScore(stuList);
	sort(stuList.begin(), stuList.end(), cmp);
	printStuList(stuList);
}
