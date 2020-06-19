#include <iostream>
using namespace std;

// 关键词
const int codeKey = 1;
// 标识符
const int codeVariable = 2;
// 常量
const int codeConst = 3;
// 操作符
const int codeOperator = 4;
// 分隔符
const int codeDivide = 5;

struct info
{
	int code;
	string str;
};

bool isKey(string & s)
{
	static string keyList[] = {
		"if", "int", "for", "while",
		"do", "return", "break", "continue"
	};
	for(int i = 0; i < 8; i++)
	{
		if(s == keyList[i])
			return true;
	}
	return false;
}

bool isOperator(string & s)
{
	static string keyList[] = {
		"+", "-", "*", "/", "=",
		">", "<", ">=", "<=", "!="
	};
	for(int i = 0; i < 10; i++)
	{
		if(s == keyList[i])
			return true;
	}
	return false;
}

bool isDivide(const char & s)
{
	static char keyList[] = {
		',', ';', '{', '}', '(', ')'
	};
	for(int i = 0; i < 6; i++)
	{
		if(s == keyList[i])
			return true;
	}
	return false;
}

bool isNumber(string & s)
{
	int len = s.length();
	for(int i = 0; i < len; i++)
	{
		if(!isdigit(s[i]))
			return false;
	}
	return true;
}

int main()
{
	string str, input;
	while(getline(cin, input))
		str.append(input);
	// 0 - 字母，数字，下划线
	// 1 - 标点符号
	// 2 - 终止符
    int lastType = 0, nowType;
	const int len = str.length();
	int start = 0, code;
	for(int i = 0; i <= len; i++)
	{
		if(isalnum(str[i]) || str[i] == '_')
			nowType = 0;
		else if(str[i] != '\0' && str[i] != ' ')
			nowType = 1;
		else
			nowType = 2;
		if(lastType == nowType && !isDivide(str[i]))
			continue;
		if(lastType == 2)
		{
			start = i;
			lastType = nowType;
			continue;
		}
		input = str.substr(start, i - start);
		start = i;
		
		if(isKey(input))
			code = codeKey;
		else if(isNumber(input))
			code = codeConst;
		else if(isOperator(input))
			code = codeOperator;
		else if(isDivide(input[0]))
			code = codeDivide;
		else if(input != " ")
			code = codeVariable;
		else
			code = 0;

		lastType = nowType;
		if(code == 0)
			continue;
		printf("(%d, \"%s\")\n", code, input.c_str());
	}
}
