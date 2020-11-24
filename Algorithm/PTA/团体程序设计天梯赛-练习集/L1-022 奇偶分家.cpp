#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int j, o;
	j = o = 0;
	int i;
	while(n--) {
		cin >> i;
		(i % 2) ? j++ : o++;
	}
	printf("%d %d", j, o);
}
