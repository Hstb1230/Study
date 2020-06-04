#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n)
{
	if(n == 1) return false;
	if(n == 2) return true;
	int end = sqrt(n) + 1;
	for(int i = 2; i < end; i ++)
	{
		if(n % i == 0)
			return false;
	}
	return true;
}

int strToInt(string str)
{
	int n = 0, len = str.length();
	for(int i = 0; i < len; i++)
	{
		n *= 10;
		n += str[i] - '0';
	}
	return n;
}

int main()
{
	int len, k;
	cin >> len >> k;
	string str;
	int num;
	getline(cin, str);
	getline(cin, str);
	len -= k;
	for(int i = 0; i <= len; i++)
	{
		num = strToInt(str.substr(i, k));
		if(isPrime(num))
		{
			printf("%0*d", k, num);
			return 0;
		}
	}
	printf("404");
}
