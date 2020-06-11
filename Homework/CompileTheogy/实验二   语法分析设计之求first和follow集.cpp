#include <iostream>
#include <string>
#include <map>
using namespace std;
#define max 30

struct CSS       //定义一个产生式结构体
{
    char left; //定义产生式的左部
    string right; //定义产生式的右部
};
string con;//存放文法中的非终结符
map<char,string> first;//存放非终结符的first集
map<char,string> follow;//存放非终结符的follow集

// 合并字符串
bool merge(string & a, const string & b)
{
	int lenOfA = a.length();
	int len = b.length();
	for(int i = 0; i < len; i++)
	{
		if(a.find(b[i]) == string::npos)
			a.push_back(b[i]);
	}
	return a.length() != lenOfA;
}

// 合并字符串
bool merge(string & a, const char c)
{
	int lenOfA = a.length();
	if(a.find(c) == string::npos)
		a.push_back(c);
	return a.length() != lenOfA;
}

string format(const string & str)
{
	int len = str.length();
	string f(len * 2, ' ');
	for(int i = 0; i < len; i++)
	{
		f[i * 2] = str[i];
	}
	return f;
}

//提取产生式的非终结符
void search(CSS *p, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
		// 将左部加入非终结符列表
        if(con.find(p[i].left) == string::npos)
			con.push_back(p[i].left);
		for(j = 0; j < p[i].right.length(); j++)
        {
            if(isupper(p[i].right[j]))
            {
            	merge(con, p[i].right[j]);
            }
        }
    }
}

//求文法中非终结符的First集
void First(CSS *p, const int n, const char m)
{
	for(int i = 0; i < n; i++)
	{
		if(p[i].left != m)
			continue;
		int pos = -1;   // 适应最开始的pos = 0
		char c;
		do
		{
			pos++;
			c = p[i].right[pos];
			if(isupper(c))
			{
				First(p, n, c);
				merge(first[m], first[c]);
			}
			else
			{
				if(first[m].find(c) == string::npos)
					first[m].push_back(c);
			}
		} while((pos = p[i].right.find('|', pos)) != string::npos);
	}
}

//求文法的follow集
void Follow(CSS *p, int n)
{
	string f;
	char c;
	// 加入first
	for(int i = 0; i < n; i++)
	{
		f.clear();
		for(int j = p[i].right.length() - 1; j >= 0; j--)
		{
			c = p[i].right[j];
			if(c == '|')
				f.clear();
			else if(isupper(c))
			{
				merge(follow[c], f);
				merge(f, first[c]);
				if(f.find('#') != string::npos)
					f.erase(f.find('#'), 1);
			}
			else
				merge(f, c);
		}
	}
	bool isUpdate;
	char last;
	do
	{
		isUpdate = false;
		for(int i = 0; i < n; i++)
		{
			f.clear();
			last = '\0';
			for(int j = p[i].right.length() - 1; j >= 0; j--)
			{
				c = p[i].right[j];
				if(c == '|')
					f.clear();
				else if(isupper(c))
				{
					// 非终结符
					if(last == '\0')
					{
						// 最后一个非终结符
						// 将左部符号的follow给它的follow
						merge(f, follow[p[i].left]);
                        if(merge(follow[c], f))
							isUpdate = true;
					}
					else
					{
						if(merge(follow[c], follow[last]))
							isUpdate = true;
						merge(f, follow[c]);
					}
				}
				else
					merge(f, c);
				if(last == '\0')
					last = c;
			}
		}
	} while(isUpdate);
}

int main()
{
    int i, n;
    string input;
    cout << "请输入文法产生式个数N：";
    cin >> n;
    getline(cin, input);
    CSS *p = new CSS[n];   // 初始化产生式数组
    for(i = 0; i < n; i++)  //输入产生式数组,用#代表空
    {
        getline(cin, input);  //输入
        // 假定左部只有一个长度的符号
        p[i].left = input[0];
        p[i].right = input.substr(3);
    }
    search(p, n); //提取产生式中的非终结符
    cout << "请输入该文法的开始符号：";
    char s;
    cin >> s;
    cout << "该文法非终结符的first集：" << endl;
    for(i = 0; i < con.length(); i++)
    {
        First(p, n, con[i]);
        cout << con[i] << ":" << format(first[con[i]]) << endl;
    }
    cout << "该文法非终结符的follow集：" << endl;
    follow[s] = "$";
    Follow(p, n);
    for(i = 0; i < con.length(); i++)
    {
        cout << con[i] << ":" << format(follow[con[i]]) << endl;
    }
}

