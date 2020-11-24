#include <iostream>
using namespace std;

typedef struct {
	string id;
	int exam_id;
} examer;

void inputInfo(examer e[], int n) {
	int input;
	for(int i = 0; i < n; i++) {
		cin >> e[0].id >> input >> e[0].exam_id;
		e[input].id = e[0].id;
		e[input].exam_id = e[0].exam_id;
	}
}
int main() {
	int n, input;
	cin >> n;
	examer e[n + 1];
	inputInfo(e, n);
	int m;
	cin >> m;
	for(int i = 0; i < m; i++) {
		cin >> input;
		printf("%s %d\n", e[input].id.c_str(), e[input].exam_id);
	}
}
