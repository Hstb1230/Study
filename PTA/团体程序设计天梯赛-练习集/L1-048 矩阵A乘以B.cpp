#include <iostream>
#include <vector>
using namespace std;

int main() {
	int ra, ca;
	cin >> ra >> ca;
	
	int a[ra][ca];
	for(int i = 0; i < ra; i++) {
		for(int j = 0; j < ca; j++) {
			cin >> a[i][j];
		}
	}
	
	int rb, cb;
	cin >> rb >> cb;

	int b[rb][cb];
	for(int i = 0; i < rb; i++) {
		for(int j = 0; j < cb; j++) {
			cin >> b[i][j];
		}
	}
	
	if(ca != rb) {
		printf("Error: %d != %d", ca, rb);
	} else {
		printf("%d %d\n", ra, cb);
		int c[ra][cb];
		for(int i = 0; i < ra; i++) {
			int flag = 0;
			for(int j = 0; j < cb; j++) {
				c[i][j] = 0;
				for(int k = 0; k < ca; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
				if(flag++) cout << ' ';
				cout << (int)c[i][j];
			}
			cout << endl;
		}
		
	}
}
