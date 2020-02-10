#include <iostream>
#include <vector>
#define DEBUG false
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

/*
[low, mid), [mid, high)
*/
void merge(vector<int> & v, int low, int mid, int high) {
	if(low >= high) return;
	if(DEBUG)
		printf("%d,%d,%d\n", low, mid, high);
	vector<int> tmp(high - low);
	int t = 0;
	for(int i = low, j = mid; i < mid || j < high; ) {
		tmp[t++] = ((i < mid && j < high && v[i] <= v[j]) || (j >= high)) ? v[i++] : v[j++];
	}
	for(int i = 0; i < t; i++) {
		v[low + i] = tmp[i];
	}
	if(!DEBUG) return;
	printVector(tmp);
	printVector(v);
	cout << endl;
}

/* 自顶向下的归并(但是题目并不是这个) */
void mergeSortDown(vector<int> & v, vector<taskInfo> & task) {
	return;
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
	merge(v, task[a].begin, task[a].end, task[b].end);
	if(DEBUG)
		printVector(task);
}

/* 自底向上的归并 */
void mergeSortUp(vector<int> & v, int & stride) {
	if(DEBUG)
		printf("Stride: %d\n", stride);
	if(stride >= v.size()) return;
	for(int i = 0; i + stride < v.size(); i += 2 * stride) {
		merge(v, i, i + stride, ((i + 2 * stride > v.size()) ? v.size() : i + 2 * stride));
	}
	// 将步长翻倍
	// Double the stride
	stride <<= 1;
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
	int stride = 1;
	for(int i = 1; i < n; i++) {
		insertionSort(insert, 0, i);
		mergeSortUp(merge, stride);
        if(DEBUG)
			cout << "One Pass" << endl;
		if(insert == vs) {
			cout << "Insertion Sort" << endl;
			insertionSort(insert, 0, i + 1);
			printVector(insert);
		} else if(merge == vs) {
			cout << "Merge Sort" << endl;
			mergeSortUp(merge, stride);
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
