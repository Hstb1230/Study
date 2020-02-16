#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int ah, ag, bh, bg;
	int ac = 0, bc = 0;
	while(n--) {
		cin >> ah >> ag >> bh >> bg;
		if(ag == bg) continue;
		if(ag == ah + bh) {
			bc++;
		} else if(bg == ah + bh) {
			ac++;
		}
	}
	cout << ac << ' ' << bc;
}
