#include <iostream>
using namespace std;

int main() {
	int x, k;
	cin >> x >> k;
	int n1, b, t, n2;
	for(int i = 0; i < k; i++) {
		cin >> n1 >> b >> t >> n2;
		if(t > x) {
			printf("Not enough tokens.  Total = %d.\n", x);
			continue;
		}
		if((n2 > n1 && b == 1) || (n2 < n1 && b == 0)) {
			// win
			x += t;
			printf("Win %d!  Total = %d.\n", t, x);
		} else {
			// lose
            x -= t;
			printf("Lose %d.  Total = %d.\n", t, x);
			if(x == 0) {
				printf("Game Over.\n");
				break;
			}
		}
	}
}
