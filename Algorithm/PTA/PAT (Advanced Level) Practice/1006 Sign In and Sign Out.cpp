#include <iostream>
using namespace std;

int getTime()
{
	int h, m, s;
	scanf("%d:%d:%d", &h, &m, &s);
	return h * 10000 + m * 100 + s;
}

int main()
{
	int n;
	cin >> n;
	string firstPerson, lastPerson;
	int firstTime = 235959, lastTime = 0;
	string id; int in, out;
	for(int i = 0; i < n; i++)
	{
		cin >> id;
		in = getTime();
		out = getTime();
		if(out < in)
			out += 240000;
		if(in < firstTime)
		{
			firstPerson = id;
			firstTime = in;
		}
		if(out > lastTime)
		{
			lastPerson = id;
			lastTime = out;
		}
	}
	cout << firstPerson << " " << lastPerson;
}
