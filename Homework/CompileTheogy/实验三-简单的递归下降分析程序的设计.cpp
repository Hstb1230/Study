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
		printf("请输入一个语句，以#号结束语句（直接输入#号退出）\n");
		if(!(scanf("%s", &s) && (s[0] != '#')))
			break;
		sign = 0;
		i = 0;
		E();
		if(s[i] == '#')
			printf("正确语句\n");
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
			printf("语句有误\n");
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
			printf("语句有误\n");
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
				printf("语句有误\n");
				sign = 1;
				++i;
			}
		}
		else if(s[i] == 'i')
			++i;
		else 
		{
			printf("语句有误\n");
			sign = 1;
		}
	}
}
