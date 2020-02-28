#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef struct {
	int full_score, answer_count, true_answer_count;
	vector<char> true_answer;
} question;

typedef pair<double, int> mp;

bool cmp(mp a, mp b) {
	if(a.second != b.second)
		return a.second > b.second;
	else if((int)a.first != (int)b.first)
		return (int)a.first < (int)b.first;
	else
		return ((int)(a.first * 10) % 10) < ((int)(b.first * 10) % 10);
}

void print_wrong(map<double, int> wrong) {
	vector<mp> mps(wrong.begin(), wrong.end());
	sort(mps.begin(), mps.end(), cmp);
	int len = mps.size();
	printf("====\n");
	for(int i = 0; i < len; i++) {
		printf("%d %d-%c\n", mps[i].second, (int)mps[i].first, ('a' + (int)(mps[i].first * 10) % 10));
//		printf("%d-%c\n", (int)mps[i].first, ('a' + (int)(mps[i].first * 10) % 10));
	}
	printf("====\n");
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<question> q(m);
	map<double, int> wrong;
	for(int i = 0; i < m; i++) {
		cin >> q[i].full_score >> q[i].answer_count >> q[i].true_answer_count;
		q[i].true_answer.resize(q[i].true_answer_count);
		for(int j = 0; j < q[i].true_answer_count; j++) {
			cin >> q[i].true_answer[j];
			wrong[(i + 1 + 0.1 * (q[i].true_answer[j] - 'a'))] = n;
		}
	}
//	print_wrong(wrong);
	
	string all_answers;
	const char * loc;
	int choose_count, flag;
	char choose;
	double sum;
	for(int i = 0; i <= n; i++) {
		getline(cin, all_answers);
		if(all_answers == "") continue;
		loc = all_answers.c_str();
		sum = 0;
		for(int j = 0; j < m; j++) {
			flag = 0;
			while(*loc != '(') loc++;
			loc++;
			sscanf(loc, "%d", &choose_count);
//			printf("%d ", choose_count);
			for(int k = 0; k < choose_count; k++) {
				loc += 2;
				sscanf(loc, "%c", &choose);
//				printf("%c ", choose);
				if(find(q[j].true_answer.begin(), q[j].true_answer.end(), choose) != q[j].true_answer.end()) {
					wrong[(j + 1 + 0.1 * (choose - 'a'))]--;
					if(flag >= 0)
						flag++;
				} else {
					flag = -1;
					// Maybe Input Invaild Choose
					if((choose - 'a') <= q[j].answer_count)
						wrong[(j + 1 + 0.1 * (choose - 'a'))]++;
				}
			}
			if(flag == -1) {
				// have wrong
			} else if(flag == q[j].true_answer_count) {
				// true
				sum += q[j].full_score;
			} else {
				// part of true
				sum += 0.5 * q[j].full_score;
			}
//			printf("%d %.1f\n", flag, sum);
		}
//		print_wrong(wrong);
		printf("%.1f\n", sum);
	}
	vector<mp> mps(wrong.begin(), wrong.end());
	sort(mps.begin(), mps.end(), cmp);
	int len = mps.size();
	flag = 1;
	for(int i = 0; i < len; i++) {
		if(i == 0 && mps[i].second <= 0) {
			flag = 0;
			break;
		}
		if(i > 0 && mps[i].second != mps[i - 1].second)
			break;
		printf("%d %d-%c\n", mps[i].second, (int)mps[i].first, ('a' + (int)(mps[i].first * 10) % 10));
	}
	if(flag == 0)
		printf("Too simple");
}
