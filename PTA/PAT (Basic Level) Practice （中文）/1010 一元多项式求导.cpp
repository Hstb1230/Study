#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct {
	int a;
	int b;
} x;

int main() {
	vector<x> xs;
	x xi;
	
	while(cin >> xi.a >> xi.b) {
		xi.a *= xi.b;
		xi.b = max(xi.b - 1, 0);
		xs.push_back(xi);
	}
	
	for(int i = 0; i < xs.size(); i++) {
		if(xs[i].a == 0 && i != 0) continue;
		if(i != 0) cout << ' ';
		printf("%d %d", xs[i].a, xs[i].b);
	}
}
