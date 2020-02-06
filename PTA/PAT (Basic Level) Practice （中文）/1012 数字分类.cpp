#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printVector(const vector<int> v) {
	return;
	cout << endl;
	for(int i = 0; i < v.size(); i++) {
		if(i > 0) cout << ' ';
		cout << v[i];
	}
	cout << endl;
}

void printVector(const vector<double> v) {
	return;
	cout << endl;
	for(int i = 0; i < v.size(); i++) {
		if(i > 0) cout << ' ';
		printf("%.2f", v[i]);
	}
	cout << endl;
}

int main() {
	vector< vector<int> > v(6);
	for(int i = 1; i < 6; i++)
		v[i].clear();

	int n;
	cin >> n;
	int a;
	while(n--) {
		cin >> a;
		switch(a % 5) {
			case 0:
				if(a % 2 == 0)
					v[1].push_back(a);
				break;

			case 1:
				v[2].push_back(a);
				break;

			case 2:
				v[3].push_back(a);
				break;

			case 3:
				v[4].push_back(a);
				break;

			case 4:
				v[5].push_back(a);
				break;
		}
	}
	int a1, a2, a3, a5;
	double a4;
	a1 = a2 = a3 = a4 = a5 = 0;
	
	printVector(v[1]);
	for(int i = 0; i < v[1].size(); i++) {
		a1 += v[1][i];
	}
	if(v[1].size())
		cout << a1 << ' ';
	else
		cout << "N ";

	printVector(v[2]);
	for(int i = 0; i < v[2].size(); i++) {
		if(i % 2 == 0)
			a2 += v[2][i];
		else
			a2 -= v[2][i];
	}
	if(v[2].size())
		cout << a2 << ' ';
	else
		cout << "N ";

	printVector(v[3]);
	a3 = v[3].size();
	if(v[3].size())
		cout << a3 << ' ';
	else
		cout << "N ";

	printVector(v[4]);
	for(int i = 0; i < v[4].size(); i++) {
		a4 += v[4][i];
	}
	if(v[4].size()) {
		a4 /= v[4].size();
//		a4 += 0.05;
		printf("%.1f ", a4);
	} else
		cout << "N ";

	printVector(v[5]);
	if(v[5].size()) {
		sort(v[5].begin(), v[5].end());
		a5 = v[5][(v[5].size() - 1)];
		cout << a5;
	} else
		cout << "N";

	
}
