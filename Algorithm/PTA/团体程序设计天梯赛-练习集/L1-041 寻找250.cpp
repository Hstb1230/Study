#include <iostream>
using namespace std;

int main() {
	int num;
	int count = 0;
	while(cin >> num) {
		count++;
		if(num == 250) {
			cout << count;
			break;
		}
	}
	return 0;
}
