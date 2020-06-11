#include <iostream>
#include <string>
#include <map>
using namespace std;
#define max 30

struct CSS       //����һ������ʽ�ṹ��
{
    char left; //�������ʽ����
    string right; //�������ʽ���Ҳ�
};
string con;//����ķ��еķ��ս��
map<char,string> first;//��ŷ��ս����first��
map<char,string> follow;//��ŷ��ս����follow��

// �ϲ��ַ���
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

// �ϲ��ַ���
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

//��ȡ����ʽ�ķ��ս��
void search(CSS *p, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
		// ���󲿼�����ս���б�
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

//���ķ��з��ս����First��
void First(CSS *p, const int n, const char m)
{
	for(int i = 0; i < n; i++)
	{
		if(p[i].left != m)
			continue;
		int pos = -1;   // ��Ӧ�ʼ��pos = 0
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

//���ķ���follow��
void Follow(CSS *p, int n)
{
	string f;
	char c;
	// ����first
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
					// ���ս��
					if(last == '\0')
					{
						// ���һ�����ս��
						// ���󲿷��ŵ�follow������follow
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
    cout << "�������ķ�����ʽ����N��";
    cin >> n;
    getline(cin, input);
    CSS *p = new CSS[n];   // ��ʼ������ʽ����
    for(i = 0; i < n; i++)  //�������ʽ����,��#�����
    {
        getline(cin, input);  //����
        // �ٶ���ֻ��һ�����ȵķ���
        p[i].left = input[0];
        p[i].right = input.substr(3);
    }
    search(p, n); //��ȡ����ʽ�еķ��ս��
    cout << "��������ķ��Ŀ�ʼ���ţ�";
    char s;
    cin >> s;
    cout << "���ķ����ս����first����" << endl;
    for(i = 0; i < con.length(); i++)
    {
        First(p, n, con[i]);
        cout << con[i] << ":" << format(first[con[i]]) << endl;
    }
    cout << "���ķ����ս����follow����" << endl;
    follow[s] = "$";
    Follow(p, n);
    for(i = 0; i < con.length(); i++)
    {
        cout << con[i] << ":" << format(follow[con[i]]) << endl;
    }
}

