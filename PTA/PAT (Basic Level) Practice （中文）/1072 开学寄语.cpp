#include <iostream>
#include <map>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	map<int, bool> things;
	int id;
	for(int i = 0; i < m; i++) {
		cin >> id;
		things[id] = true;
	}
	string stu_name;
	int thing_count, flag = 0;
	int stu_sum = 0, thing_sum = 0;
	for(int i = 0; i < n; i++) {
		flag = 0;
		cin >> stu_name >> thing_count;
		for(int j = 0; j < thing_count; j++) {
			cin >> id;
			if(things.count(id) > 0) {
				if(++flag == 1) {
					stu_sum++;
					printf("%s:", stu_name.c_str());
				}
				thing_sum++;
				printf(" %04d", id);
			}
		}
		if(flag > 0) printf("\n");
	}
	printf("%d %d", stu_sum, thing_sum);
}
