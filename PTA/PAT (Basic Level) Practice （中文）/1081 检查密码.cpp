#include <iostream>
using namespace std;

int main()
{
	int n;
	string pwd;
	bool isVaild;
	int len, cPoint, cAlpha, cDigit;
	cin >> n;
	getline(cin, pwd);
	while(n--)
	{
		getline(cin, pwd);
//		cin >> pwd;
		len = pwd.length();
		if(len < 6)
		{
			printf("Your password is tai duan le.\n");
			continue;
		}
		isVaild = true;
		cPoint = cAlpha = cDigit = 0;
		for(int i = 0; i < len; i++)
		{
			if(pwd[i] == '.')
				cPoint++;
			else if(isalpha(pwd[i]))
				cAlpha++;
			else if(isdigit(pwd[i]))
				cDigit++;
			else
			{
				isVaild = false;
				break;
			}
		}
		if(!isVaild)
		{
			printf("Your password is tai luan le.\n");
		}
		else if(cAlpha == 0)
		{
			printf("Your password needs zi mu.\n");
		}
		else if(cDigit == 0)
		{
			printf("Your password needs shu zi.\n");
		}
		else
		{
			printf("Your password is wan mei.\n");
		}
	}
}
