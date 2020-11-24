#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int sum = 0;
	for(int i = a; i <= b; i++) {
		sum += i;
		printf("%5d", i);
		if((i - a) % 5 == 4 || i == b) cout << endl;
	}
	printf("Sum = %d", sum);
}
