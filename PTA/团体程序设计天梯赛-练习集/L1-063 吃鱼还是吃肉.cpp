#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	while(n--) {
		int sex, h, w;
		cin >> sex >> h >> w;
		
		if(sex == 1) {
			if(h < 130) {
				cout << "duo chi yu!";
			} else if(h == 130) {
				cout << "wan mei!";
			} else {
				cout << "ni li hai!";
			}
			cout << ' ';
			if(w < 27) {
				cout << "duo chi rou!";
			} else if(w == 27) {
				cout << "wan mei!";
			} else {
				cout << "shao chi rou!";
			}
			cout << endl;
		} else {
			if(h < 129) {
				cout << "duo chi yu!";
			} else if(h == 129) {
				cout << "wan mei!";
			} else {
				cout << "ni li hai!";
			}
			cout << ' ';
			if(w < 25) {
				cout << "duo chi rou!";
			} else if(w == 25) {
				cout << "wan mei!";
			} else {
				cout << "shao chi rou!";
			}
			cout << endl;
		}
	}
}
