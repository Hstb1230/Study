#include <iostream>
using namespace std;

bool isVaild(const string num) {
	int level[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
	int sum = 0;
	for(int i = 0; i < 17; i++) {
		if(!isdigit(num[i])) return false;
		sum += (num[i] - '0') * level[i];
	}
	int z = sum % 11;
	int m[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
	return *num.rbegin() == m[z];
}

int main() {
	int n;
	cin >> n;
	string num;
	bool flag = true;
	while(n--) {
		cin >> num;
		if(isVaild(num)) continue;
		flag = false;
		cout << num << endl;
	}
	if(flag) cout << "All passed" << endl;
}
