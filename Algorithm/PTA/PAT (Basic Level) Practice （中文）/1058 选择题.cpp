#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	int full;
	int num;
	int true_ans;
	vector<char> ans;
	int id;
	int wrong;
} problem;

bool cmp(problem a, problem b) {
	if(a.wrong == b.wrong)
		return a.id < b.id;
	return a.wrong > b.wrong;
}

void printProblems(vector<problem> p) {
	int len = p.size();
	for(int i = 0; i < len; i++) {
		printf("%d: %d\n", p[i].id, p[i].wrong);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<problem> p(m);
	for(int i = 0; i < m; i++) {
		cin >> p[i].full >> p[i].num >> p[i].true_ans;
		p[i].id = i + 1;
		p[i].wrong = 0;
		p[i].ans.resize(p[i].true_ans);
		for(int j = 0; j < p[i].true_ans; j++)
			cin >> p[i].ans[j];
		sort(p[i].ans.begin(), p[i].ans.end());
	}
	string ans_string;
	const char * tmp;
	int loc, num;
	vector<char> choose;
	vector<int> score(n + 1, 0);
	for(int i = 0; i <= n; i++) {
		getline(cin, ans_string);
		if(ans_string == "") continue;
		loc = 0;
		tmp = ans_string.c_str();
		for(int j = 0; j < m; j++) {
			loc = ans_string.find('(', loc) + 1;
			sscanf(tmp + loc, "%d", &num);
			choose.resize(num);
			for(int k = 0; k < num; k++) {
				sscanf(tmp + loc + (k + 1) * 2, "%c", &choose[k]);
			}
			sort(choose.begin(), choose.end());
			if(choose != p[j].ans)
				p[j].wrong++;
			else
				score[i] += p[j].full;
		}
	}
	for(int i = 1; i <= n; i++) {
		cout << score[i] << endl;
	}
	sort(p.begin(), p.end(), cmp);
//	printProblems(p);
    if(p[0].wrong == 0)
		cout << "Too simple" << endl;
	else {
		printf("%d %d", p[0].wrong, p[0].id);
		for(int i = 1; i < p.size(); i++) {
			if(p[i].wrong != p[i - 1].wrong)
				break;
			printf(" %d", p[i].id);
		}
	}

}
