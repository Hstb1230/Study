#include <iostream>
#include <cmath>
using namespace std;

int main() {
	double kg, m;
	cin >> kg >> m;
	
	double ratio = kg / pow(m, 2);
	printf("%.1f\n", ratio);
	if(ratio <= 25) {
		cout << "Hai Xing";
	} else
		cout << "PANG";
}
