#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int h, m;
		cin >> h >> m;
		int standard = (h - 100) * 0.9 * 2;
		int diff = fabs(m - standard);
		if(diff < standard * 0.1) cout << "You are wan mei!";
		else if(m > standard) cout << "You are tai pang le!";
		else if(m < standard) cout << "You are tai shou le!";
		cout << endl;
	}
}
