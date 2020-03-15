#include <iostream>
using namespace std;

string int_to_string(int n)
{
	char chars[1000] = "";
	sprintf(chars, "%d", n);
	return chars;
}

int main()
{
	string s;
	getline(cin, s);
	bool decode = (s == "D");
	getline(cin, s);
	int len = s.length();
	string ret;
	char last = s[0];
	int t = 0;
	int sum = 0;
	for(int i = 0; i <= len; i++)
	{
		if(isdigit(s[i]) && decode)
		{
			// 是数字, 需要增加解压数量
			sum *= 10;
			sum += s[i] - '0';
		}
		else if(sum != 0)
		{
			// 遇到非数字, 但是又前面存在字符数量
			ret.append(sum, s[i]);
			sum = 0;
		}
		else if(last == s[i] && !decode)
		{
			// 相同文本, 增加字符数量
			t++;
		}
		else 
		{
			// 不相同文本, 判断是否需要加数字
			if(t > 1)
			{
				ret.append(int_to_string(t));
				t = 1;
			}
			if(decode)
				ret.append(1, s[i]);
			else
				ret.append(1, last);
		}
		last = s[i];
	}
	cout << ret;
}
