#include <iostream>
using namespace std;
#define CLK_TCK 100.0

int main() {
	int c1, c2;
	cin >> c1 >> c2;
	int runTime = (c2 - c1) / CLK_TCK + 0.5;
	printf("%02d:%02d:%02d", (runTime / 3600), ((runTime % 3600) / 60), (runTime % 60));
}
