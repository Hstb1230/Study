#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		string id;
		cin >> id;

		if(id == "") continue;
		
		int suma, sumb;
		suma = sumb = 0;
		
		for(int i = 0; i < 3; i++) {
			suma += id[i] - '0';
		}
		
		for(int i = 3; i < 6; i++) {
			sumb += id[i] - '0';
		}
		
		if(suma == sumb) {
			cout << "You are lucky!" << endl;
		} else {
			cout << "Wish you good luck." << endl;
		}
	}
}
