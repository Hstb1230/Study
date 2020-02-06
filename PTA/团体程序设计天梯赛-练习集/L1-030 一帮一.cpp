#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	struct {
		int sex;
		string name;
	} stu[n];
	for(int i = 0; i < n; i++) {
		cin >> stu[i].sex >> stu[i].name;
	}
	for(int i = 0; i < n / 2; i++) {
		cout << stu[i].name;
		cout << ' ';
		for(int j = n - 1; j > 0; j--) {
			if(stu[j].sex != -1 && stu[j].sex != stu[i].sex) {
				stu[j].sex = -1;
				cout << stu[j].name;
				break;
			}
		}
		cout << endl;
	}
}
