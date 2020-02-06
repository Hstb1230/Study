#include <iostream>
using namespace std;
void changeAB(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}
int main() {
	int n = 3;
	int a[n];
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for(int i = 0; i < n; i++) {
		int min = i;
		for(int j = i; j < n; j++) {
			if(a[j] < a[min]) min = j;
		}
		if(min != i) {
			changeAB(a[i], a[min]);
		}
	}
	for(int i = 0; i < n; i++) {
		if(i > 0) cout << "->";
		cout << a[i];
	}
}
