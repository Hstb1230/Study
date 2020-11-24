#include <iostream>
using namespace std;

int getL(int n, int & diff) {
	int sum = 1, line = 1, every = 6;
	while((sum + every) <= n) {
		sum += every;
		line++;
		every += 4;
	}
	// cout << every << ' ' << sum << endl;
	diff = n - sum;
	return line;
}

void printChar(int begin, int end, char c) {
	int diff = 1;
	if(begin > end) diff = -1;
	int len = 2 * begin + 1;
	for(int i = begin; i != end + diff; i += diff) {
		for(int j = (begin > end ? begin : end) - i; j > 0; j--)
			cout << ' ';
        for(int j = 2 * i - 1; j > 0; j--)
        	cout << c;
		cout << endl;
	}
}

int main() {
	int n; char c;
	cin >> n >> c;
	int diff;
	int line = getL(n, diff);
	printChar(line, 1, c);
	if(line > 1)
		printChar(2, line, c);
	cout << diff;
}
