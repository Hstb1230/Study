#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		char sex;
		double h;
		cin >> sex >> h;
		// cout << sex << ' ' << h << endl;
		if(sex == 'M')
			printf("%.2f\n", h / 1.09);
		else
			printf("%.2f\n", h * 1.09);
	}
}
