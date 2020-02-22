#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	int a, b;
	double max = 0, tmp;
	for(int i = 0; i < n; i++) {
		cin >> a >> b;
		tmp = sqrt(a * a + b * b);
		if(tmp > max)
			max = tmp;
	}
	printf("%.2f\n", max);
}
