#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int d;
	cin >> d;
	cout << max((d + 2) % 8, d - 5);
}
