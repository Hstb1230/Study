#include <iostream>
using namespace std;

int main() {
	int hh, mm;
	scanf("%d:%d", &hh, &mm);
	if(hh >= 0 && hh <= 12) {
		printf("Only %02d:%02d.  Too early to Dang.", hh, mm);
	} else {
		hh -= 12;
		if(mm != 0) hh++;
		while(hh--) cout << "Dang";
	}
}
