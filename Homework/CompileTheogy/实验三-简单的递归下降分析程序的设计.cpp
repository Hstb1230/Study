#include <cstdio>
void E();
void T();
void E1();
void T1();
void F();

char s[100];
int i, sign;

int main()
{
	while(true)
	{
		printf("������һ����䣬��#�Ž�����䣨ֱ������#���˳���\n");
		if(!(scanf("%s", &s) && (s[0] != '#')))
			break;
		sign = 0;
		i = 0;
		E();
		if(s[i] == '#')
			printf("��ȷ���\n");
	}
}

void E()
{
	if(sign == 0)
	{
		T();
		E1();
	}
}

void E1()
{
	if(sign == 0)
	{
		if(s[i] == '+')
		{
			++i;
			T();
			E1();
		}
		else if(s[i] != '#' && s[i] != ')')
		{
			printf("�������\n");
			sign = 1;
		}
	}
}

void T()
{
	if(sign == 0)
	{
		F();
		T1();
	}
}

void T1()
{
	if(sign == 0)
	{
		if(s[i] == '*')
		{
			++i;
			F();
			T1();
		}
		else if(s[i] != '#' && s[i] != ')' && s[i] != '+')
		{
			printf("�������\n");
			sign = 1;
		}
	}
}

void F()
{
	if(sign == 0)
	{
		if(s[i] == '(')
		{
			++i;
			E();
			if(s[i] == ')')
				++i;
			else if(s[i] == '#')
			{
				printf("�������\n");
				sign = 1;
				++i;
			}
		}
		else if(s[i] == 'i')
			++i;
		else 
		{
			printf("�������\n");
			sign = 1;
		}
	}
}
