#include<string.h>
#include<iostream>
using namespace std;

char prog[80], token[8];
char ch;
int syn, p, m = 0, n, row, sum = 0;
const char * rwtab[6] = { "begin", "if", "then", "while", "do", "end" };

void scaner()
{
	for(n = 0; n < 8; n++)
		token[n] = NULL;
	ch = prog[p++];
	while(ch == ' ')
	{
		ch = prog[p];
		p++;
	}
	if(isalpha(ch))
	{
		m = 0;
		while(isalnum(ch))
		{
			token[m++] = ch;
			ch = prog[p++];
		}
		token[m++] = '\0';
		p--;
		syn = 10;
		for(n = 0; n < 6; n++)
			if(strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;
				break;
			}
	}
	else if(isdigit(ch))
	{
		{
			sum = 0;
			while(isdigit(ch))
			{
				sum = sum * 10 + ch - '0';
				ch = prog[p++];
			}
		}
		p--;
		syn = 11;
		if(sum > 32767)
			syn = -1;
	}
	else switch(ch)
	{
		case '<':
			m = 0;
			token[m++] = ch;
			ch = prog[p++];
			if(ch == '>')
			{
				syn = 21;
				token[m++] = ch;
			}
			else if(ch == '=')
			{
				syn = 22;
				token[m++] = ch;
			}
			else
			{
				syn = 23;
				p--;
			}
			break;
		case '>':
			m = 0;
			token[m++] = ch;
			ch = prog[p++];
			if(ch == '=')
			{
				syn = 24;
				token[m++] = ch;
			}
			else
			{
				syn = 20;
				p--;
			}
			break;
		case ':':
			m = 0;
			token[m++] = ch;
			ch = prog[p++];
			if(ch == '=')
			{
				syn = 17;
				token[m++] = ch;
			}
			else
			{
				syn = 18;
				p--;
			}
			break;
		case '*':
			syn = 13;
			token[0] = ch;
			break;
		case '/':
			syn = 14;
			token[0] = ch;
			break;
		case '+':
			syn = 15;
			token[0] = ch;
			break;
		case '-':
			syn = 16;
			token[0] = ch;
			break;
		case '=':
			syn = 25;
			token[0] = ch;
			break;
		case ';':
			syn = 26;
			token[0] = ch;
			break;
		case '(':
			syn = 27;
			token[0] = ch;
			break;
		case ')':
			syn = 28;
			token[0] = ch;
			break;
		case '#':
			syn = 0;
			token[0] = ch;
			break;
		case '\n':
			syn = -2;
			break;
		default:
			syn = -1;
			break;
	}
}

int main()
{
	p = 0;
	row = 1;
	cout << "Please input string:" << endl;
	do
	{
		cin.get(ch);
		prog[p++] = ch;
	} while(ch != '#');
	p = 0;
	do
	{
		scaner();
		switch(syn)
		{
			case 11:
				printf("(%d, %d)\n", syn, sum);
				break;
			case -1:
				printf("Error in row : %d\n", row);
				break;
			case -2:
				row = row++;
				break;
			default:
				printf("(%d, %s)\n", syn, token);
				break;
		}
	} while(syn != 0);
}

