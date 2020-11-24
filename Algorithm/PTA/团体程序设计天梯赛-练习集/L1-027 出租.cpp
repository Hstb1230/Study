#include <iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	int num[10] = {0};
	for(int i = 0; s[i]; i++) {
		num[s[i] - '0']++;
	}
	int arr[10];
	int seq = 0;
	for(int i = 9; i >= 0; i--) {
		if(num[i]) arr[i] = seq++;
	}
	cout << "int[] arr = new int[]{";
	int flag = 0;
	for(int i = 9; i >= 0; i--) {
		if(!num[i]) continue;
		if(++flag > 1) cout << ',';
		cout << i;
	}
	cout << "};" << endl;
	cout << "int[] index = new int[]{";
	flag = 0;
	for(int i = 0; s[i]; i++) {
		if(++flag > 1) cout << ',';
		cout << arr[s[i] - '0'];
	}
	cout << "};" << endl;
	
}
