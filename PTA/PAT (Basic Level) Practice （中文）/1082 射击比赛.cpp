#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct conestant
{
	int id;
	int x;
	int y;
	int distance;   // æ‡¿Î
};

bool cmp(conestant a, conestant b)
{
	return a.distance < b.distance;
}

int main()
{
	int n;
	cin >> n;
	conestant c[n];
	for(int i = 0; i < n; i++)
	{
		cin >> c[i].id >> c[i].x >> c[i].y;
		c[i].x = abs(c[i].x);
		c[i].y = abs(c[i].y);
		c[i].distance = sqrt(c[i].x * c[i].x + c[i].y * c[i].y);
	}
	
	sort(c, c + n, cmp);
	
	printf("%04d %04d", c[0].id, c[n - 1].id);
}
