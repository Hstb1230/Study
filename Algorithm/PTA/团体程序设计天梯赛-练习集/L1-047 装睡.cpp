#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	string name;
	int frequency, pulse;
	while(n--) {
		cin >> name >> frequency >> pulse;
		if(!(frequency >= 15 && frequency <= 20)
			|| !(pulse >= 50 && pulse <= 70))
		{
			cout << name << endl;
		}
	}
}
