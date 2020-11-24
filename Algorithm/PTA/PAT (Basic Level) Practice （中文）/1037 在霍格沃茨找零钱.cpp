#include <iostream>
#include <vector>
#define N 3
using namespace std;

typedef vector<int> money;

void printMoney(money m);

void sub(money A, money P, money & R) {
	int rate[] = {1, 17, 29};
	int flag = 0;
	for(int i = N - 1; i >= 0; i--)
		flag += (A[i] >= P[i]) ? 1 : -1;
	if(flag <= 0) A.swap(P);
//	cout << flag << endl;
//	printMoney(A);
//	printMoney(P);
	int j;
	for(int i = N - 1; i >= 0; i--) {
		R[i] = A[i] - P[i];
//		printf("[%d]%d\n", i, R[i]);
		if(R[i] < 0) {
			for(j = i - 1; j >= 0; j--) {
				if(A[j] > 0) {
					A[j]--;
					break;
				}
			}
			if(j >= 0) {
				for(j++; j < i; j++) {
//					printf("%d:%d\n", j, rate[j]);
					A[j] += rate[j] - 1;
				}
				R[j] += rate[j];
			}
			else
				break;
		}
//		printMoney(A);
	}
	if(flag <= 0) {
		for(int i = 0; i < N; i++) {
			if(R[i]) {
				R[i] = -R[i];
				break;
			}
		}
	}
}

void printMoney(money m) {
	int flag = 0;
	for(int i = 0; i < 3; i++) {
		if(m[i] < 0) {
			flag = 1;
			m[i] = -m[i];
		}
	}
	if(flag) cout << '-';
	flag = 0;
	for(int i = 0; i < 3; i++) {
		if(flag++) cout << '.';
		cout << m[i];
	}
	cout << endl;
}

int main() {
	money P(3), A(3), R(3);
	scanf("%d.%d.%d", &P[0], &P[1], &P[2]);
	scanf("%d.%d.%d", &A[0], &A[1], &A[2]);
	sub(A, P, R);
	printMoney(R);
}

