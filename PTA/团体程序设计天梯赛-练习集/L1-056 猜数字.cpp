#include <iostream>
#include <cmath>
using namespace std;

typedef struct {
	string name;
	int guess;
} people;

int main() {
	int n;
	cin >> n;
	people p[n];
	int sum = 0;
	for(int i = 0; i < n; i++) {
		cin >> p[i].name >> p[i].guess;
		sum += p[i].guess;
	}
	double avg = 0.5 * sum / n;
	double min_value = avg;
	int min_index = 0;
	for(int i = 0; i < n; i++) {
		if(abs(avg - p[i].guess) < min_value) {
			min_value = abs(avg - p[i].guess);
			min_index = i;
		}
	}
	printf("%d %s", (int)avg, p[min_index].name.c_str());
}
