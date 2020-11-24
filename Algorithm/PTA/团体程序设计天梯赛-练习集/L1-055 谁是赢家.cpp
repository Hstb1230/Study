#include <iostream>
using namespace std;

int main() {
	int Pa, Pb;
	cin >> Pa >> Pb;
	int Ta, Tb;
	Ta = Tb = 0;
	for(int i = 0; i < 3; i++) {
		int tmp;
		cin >> tmp;
		(tmp == 0) ? Ta++ : Tb++;
	}
	if(Ta == 3 || (Pa > Pb && Ta >= 1)) {
		printf("The winner is a: %d + %d", Pa, Ta);
	} else {
		printf("The winner is b: %d + %d", Pb, Tb);
	}
}
