#include <iostream>
#include <algorithm>
using namespace std;

int countChar(string str, int & P, int & A, int & T, int & e, int & s, int & t) {
	P = 0, A = 0, T = 0, e = 0, s = 0, t = 0;
	for(int i = str.length() - 1; i >= 0; i--) {
		if(str[i] == 'P')
			P++;
		else if(str[i] == 'A')
			A++;
		else if(str[i] == 'T')
			T++;
		else if(str[i] == 'e')
			e++;
		else if(str[i] == 's')
			s++;
		else if(str[i] == 't')
			t++;
	}
	int count = min(P, min(A, min(T, min(e, min(s, t)))));
	P -= count;
	A -= count;
	T -= count;
	e -= count;
	s -= count;
	t -= count;
	return count;
}

int main() {
	string str;
	getline(cin, str);
	int P, A, T, e, s, t;
	int count = countChar(str, P, A, T, e, s, t);
	for(int i = 0; i < count; i++)
		printf("PATest");
	while(max(P, max(A, max(T, max(e, max(s, t))))) > 0) {
		if(P-- > 0)
			printf("P");
		if(A-- > 0)
			printf("A");
		if(T-- > 0)
			printf("T");
		if(e-- > 0)
			printf("e");
		if(s-- > 0)
			printf("s");
		if(t-- > 0)
			printf("t");
	}
}
