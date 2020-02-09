#include <iostream>
#include <vector>
using namespace std;

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

void mergeSort(vector<int> & v, int seq) {
	if((seq - 1) * 2 > v.size()) return;
	
}

void printVector(const vector<int> & v) {
	int flag = 0;
	for(vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		if(flag++ > 0) cout << ' ';
		cout << *it;
	}
	cout << endl;
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
	for(int i = 1; i < n; i++) {
		insertionSort(insert, 0, i);
		if(insert == vs) {
			cout << "Insertion Sort" << endl;
			insertionSort(insert, 0, i + 1);
			printVector(insert);
		} else {
			continue;
		}
		break;
	}
}
