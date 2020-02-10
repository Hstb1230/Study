#include <iostream>
#include <vector>
#define DEBUG true
using namespace std;

typedef struct {
	int begin;
	int end;
} taskInfo;

void printVector(const vector<int> & v) {
	int flag = 0;
	for(vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		if(flag++ > 0) cout << ' ';
		cout << *it;
	}
	cout << endl;
}

void printVector(const vector<taskInfo> & v) {
	if(!DEBUG) return;
	int flag = 0;
	for(vector<taskInfo>::const_iterator it = v.begin(); it != v.end(); it++) {
		if(flag++ > 0) cout << '|';
		if(it->begin + 1 == it->end)
			cout << it->begin;
		else
			cout << it->begin << "->" << it->end;
	}
	cout << endl;
}

void insertionSort(vector<int> & v, int start, int end) {
	if(end >= v.size()) return;
	int i = start;
	for(; i < end; i++)
		if(v[i] > v[end]) break;
	int value = v[end];
	for(int j = end; j > i; j--)
		v[j] = v[j - 1];
	v[i] = value;
}
int getTaskSize(const taskInfo & info) {
	return info.end - info.begin;
}

void merge(vector<int> & v, vector<taskInfo> & task, int a, int b) {
	if(a == b) return;
	if(DEBUG)
		printf("%d,%d\n", a, b);
	int i = 0, j = 0, k = 0;
	vector<int> tmp(getTaskSize(task[a]) + getTaskSize(task[b]));
	while(i < getTaskSize(task[a]) && j < getTaskSize(task[b])) {
		if(v[task[a].begin + i] <= v[task[b].begin + j])
			tmp[k++] = v[task[a].begin + i++];
		else
			tmp[k++] = v[task[b].begin + j++];
	}
	while(i < getTaskSize(task[a])) {
		tmp[k++] = v[task[a].begin + i++];
	}
	while(j < getTaskSize(task[b])) {
		tmp[k++] = v[task[b].begin + j++];
	}
	if(DEBUG)
		printVector(tmp);
	for(i = 0; i < k; i++) {
		v[task[a].begin + i] = tmp[i];
	}
	task[a].end = task[b].end;
	task.erase(task.begin() + b);
}

/* 自顶向下的归并(但是题目并不是这个) */
void mergeSortDown(vector<int> & v, vector<taskInfo> & task) {
	if(task.size() == 0) {
		task.resize(v.size());
		for(int i = task.size() - 1; i >= 0; i--) {
			task[i].begin = i;
			task[i].end = i + 1;
		}
		if(DEBUG) {
			cout << "Reset Task" << endl;
			printVector(task);
			cout << endl;
		}

	}
	if(DEBUG)
		cout << endl;
	if(task.size() <= 1) return;
	int a = 0, b = 0;
	for(int i = 0; i + 1 <= task.size(); i++) {
		if(getTaskSize(task[i]) == getTaskSize(task[i + 1]) || task.size() == 2) {
			a = i;
			b = i + 1;
			break;
		}
	}
	merge(v, task, a, b);
	if(DEBUG)
		printVector(task);
}

/* 自顶向下的归并(但是题目并不是这个) */
void mergeSortUp(vector<int> & v, vector<taskInfo> & task) {
	if(task.size() == 0) {
		task.resize(v.size());
		for(int i = task.size() - 1; i >= 0; i--) {
			task[i].begin = i;
			task[i].end = i + 1;
		}
		if(DEBUG) {
			cout << "Reset Task" << endl;
			printVector(task);
			cout << endl;
		}
	}
	if(task.size() <= 1) return;
	int a = 0, b = 0;
	for(int i = 0; i + 1 < task.size(); i++) {
		if(getTaskSize(task[i]) == getTaskSize(task[i + 1]) || task.size() == 2) {
			a = i;
			b = i + 1;
			merge(v, task, a, b);
			if(DEBUG) {
				printVector(task);
				printVector(v);
				cout << endl;
			}
		}
	}

}

int main() {
	int n;
	cin >> n;
	vector<int> v(n), vs(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	for(int i = 0; i < n; i++)
		cin >> vs[i];
	vector<int> insert(v), merge(v);
	vector<taskInfo> mergeTask;
	for(int i = 1; i < n; i++) {
		insertionSort(insert, 0, i);
		mergeSortUp(merge, mergeTask);
        if(DEBUG)
			printVector(merge);
		if(insert == vs) {
			cout << "Insertion Sort" << endl;
			insertionSort(insert, 0, i + 1);
			printVector(insert);
		} else if(merge == vs) {
			cout << "Merge Sort" << endl;
			mergeSortUp(merge, mergeTask);
			printVector(merge);
		} else {
			continue;
		}
		break;
	}
}

/*
	Reference
	https://www.jianshu.com/p/8342e60aae4f
	https://www.jianshu.com/p/33cffa1ce613
*/
