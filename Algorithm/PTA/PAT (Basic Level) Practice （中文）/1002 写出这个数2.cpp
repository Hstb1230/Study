#include <iostream>
using namespace std;
int main() {
	char s[1000];
	cin >> s;
	int sum = 0;
	for(int i = 0; s[i]; i++) {
		sum += s[i] - '0';
	}
	//cout << sum << ' ';
	//���ú�, Ȼ������, Ӱ��0��β
	int tmp = 1; //�����������
	while(sum) {
		tmp *= 10;
		tmp += sum % 10;
		sum /= 10;
	}
	sum = tmp;
	//cout << sum << endl;
	string number[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
	do{
		cout << number[sum % 10];
		sum /= 10;
		if(sum > 9) cout << ' ';
	} while(sum != 1);
}
