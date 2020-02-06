#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	if(b < 0) printf("%d/(%d)=", a, b);
	else printf("%d/%d=", a, b);
	if(b == 0) {
		cout << "Error";
	} else {
		printf("%.2f", 1.0 * a / b);
	}
}
