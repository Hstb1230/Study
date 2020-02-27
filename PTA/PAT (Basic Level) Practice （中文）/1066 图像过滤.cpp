#include <iostream>
using namespace std;

int main() {
	int m, n;
	cin >> m >> n;
	int image[m][n];
	int a, b, value;
	cin >> a >> b >> value;
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &image[i][j]);
			if(image[i][j] >= a && image[i][j] <= b) {
				image[i][j] = value;
			}
		}
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			if(j > 0) printf(" ");
			printf("%03d", image[i][j]);
		}
		printf("\n");
	}
}
