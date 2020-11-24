#include <iostream>
using namespace std;

int main() {
	int n, input;
	cin >> n;
	int v[101] = {0};
	while(n--) {
		scanf("%d", &input);
		v[input]++;
	}
	scanf("%d", &n);
	if(n == 0) return 0;
	scanf("%d", &input);
	printf("%d", v[input]);
	while(--n > 0) {
		scanf("%d", &input);
		printf(" %d", v[input]);
	}
}
