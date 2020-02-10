#include <iostream>
using namespace std;

int main() {
	int P[3], A[3];
	scanf("%d.%d.%d", &P[0], &P[1], &P[2]);
	scanf("%d.%d.%d", &A[0], &A[1], &A[2]);
	int R = (A[0] * 17 * 29 + A[1] * 29 + A[2]) - (P[0] * 17 * 29 + P[1] * 29 + P[2]);
	if(R < 0) {
		cout << '-';
		R = -R;
	}
	printf("%d.%d.%d", (R / 17 / 29), (R / 29 % 17), (R % 29));
}
