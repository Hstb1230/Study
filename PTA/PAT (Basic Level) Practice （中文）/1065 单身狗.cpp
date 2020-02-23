#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void print_single(vector<int> v) {
	int len = v.size();
	printf("%d\n", len);
	for(int i = 0; i < len; i++) {
		if(i > 0) printf(" ");
		printf("%05d", v[i]);
	}
}

int main() {
	int n;
	cin >> n;
	map<int, int> couple;
	int a, b;
	for(int i = 0; i < n; i++) {
		cin >> a >> b;
		couple[a] = b;
		couple[b] = a;
	}
	cin >> n;
	vector<int> people;
	for(int i = 0; i < n; i++) {
		cin >> a;
		people.push_back(a);
	}
	sort(people.begin(), people.end());
	vector<int>::iterator it = unique(people.begin(), people.end());
	people.erase(it, people.end());
//	print_single(people);
	
	int len = people.size();
	vector<int> single;
	for(int i = 0; i < len; i++) {
		if(couple.count(people[i]) == 0
		 || find(people.begin(), people.end(), couple[people[i]]) == people.end()) {
		 	single.push_back(people[i]);
		}
	}
	print_single(single);
	
}
