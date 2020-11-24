#include <iostream>
using namespace std;

int main() {
	int n[10];
	int min = 0;
	for(int i = 0; i < 10; i++) {
		cin >> n[i];
		if(0 == min && i > 0 && n[i] > 0) {
			min = i;
			n[i]--;
		}
	}
	cout << min;
	for(int i = 0; i < 10; i++) {
		if(n[i] <= 0) continue;
		while(n[i]--)
			cout << i;
	}
}
