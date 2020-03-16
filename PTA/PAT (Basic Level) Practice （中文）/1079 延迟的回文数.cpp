#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> int_array;
bool is_similar(const int_array & n, int_array & r)
{
	r.assign(n.begin(), n.end());
	reverse(r.begin(), r.end());
	return (n == r);
}

int_array add(const int_array & n, const int_array & r)
{
	int_array p = n, q = r;
	if(q.size() > p.size())
		p.swap(q);
	reverse(p.begin(), p.end());
	reverse(q.begin(), q.end());
	p.push_back(0);
	int len = q.size();
	for(int i = 0; i < len; i++)
	{
		p[i] += q[i];
		if(p[i] >= 10)
		{
			p[i + 1] += p[i] / 10;
			p[i] %= 10;
		}
	}
	for(int i = len; ; i++)
	{
		if(p[i] < 10)
			break;
		else if(i == p.size() - 1)
			p.push_back(0);
		p[i + 1] += p[i] / 10;
		p[i] %= 10;
	}
	reverse(p.begin(), p.end());
	if(*(p.begin()) == 0)
		p.erase(p.begin());
	return p;
}

void string_to_int(const string str, int_array & n)
{
	n.resize(str.length(), 0);
	for(int i = 0; str[i] != '\0'; i++)
	{
		n[i] = str[i] - '0';
	}
}

void print_int_array(const int_array & n)
{
	for(int_array::const_iterator i = n.begin(); i != n.end(); i++)
		printf("%d", *i);
}

int main()
{
	string str;
	cin >> str;
	int_array n, r, q;
	string_to_int(str, n);
	int t = 0;
	while(t++ < 10 && !is_similar(n, r))
	{
		print_int_array(n);
		printf(" + ");
		print_int_array(r);
		printf(" = ");
		q = add(n, r);
		print_int_array(q);
		printf("\n");
		n = q;
	}
	if(t <= 10)
	{
		print_int_array(n);
		printf(" is a palindromic number.\n");
	}
	else
		printf("Not found in 10 iterations.");
}
