#include <iostream>
#include <algorithm>
using namespace std;

typedef struct {
	double cap;
	double value;
	double price; //single
} commodity;

bool cmp(commodity a, commodity b) {
	return a.price > b.price;
}

int main() {
	int n, d;
	cin >> n >> d;
	commodity c[n];
	for(int i = 0; i < n; i++)
		cin >> c[i].cap;
	for(int i = 0; i < n; i++) {
		cin >> c[i].value;
		c[i].price = c[i].value / c[i].cap;
	}
	sort(c, c + n, cmp);
//	for(int i = 0; i < n; i++) {
//		printf("%d %d %.2f\n", c[i].cap, c[i].value, c[i].price);
//	}
	double sum = 0;
	for(int i = 0; i < n; i++) {
//		printf("%d %.2f | %d %.2f %.2f\n", d, sum, c[i].cap, c[i].value, c[i].price);
		if(c[i].cap <= d) {
			sum += c[i].value;
		} else {
			sum += d / c[i].cap * c[i].value;
		}
		d -= c[i].cap;
		if(d <= 0) break;
	}
	printf("%.2f", sum);
}
