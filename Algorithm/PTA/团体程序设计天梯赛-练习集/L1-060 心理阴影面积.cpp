#include <iostream>
using namespace std;

int main() {
	int x, y;
	cin >> x >> y;
	cout << int((100 * 100 * 0.5) - (0.5 * 100 * y) - (0.5 * 100 * (100 - x)));
}
