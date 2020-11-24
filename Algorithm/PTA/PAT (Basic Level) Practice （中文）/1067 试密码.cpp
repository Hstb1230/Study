#include <iostream>
using namespace std;

int main() {
	string password;
	int try_count;
	cin >> password >> try_count;
	string input;
	int count = 0;
	while(true) {
		getline(cin, input);
		if(input == "") continue;
		if(input == "#") break;
		if(input == password) {
			printf("Welcome in\n");
			break;
		} else {
			printf("Wrong password: %s\n", input.c_str());
			count++;
		}

		if(count == try_count) {
			cout << "Account locked" << endl;
			break;
		}
	}
}
