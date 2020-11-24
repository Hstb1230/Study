#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int time = 0, cur = 0, to;
	while(n-- > 0)
	{
		cin >> to;
		if(to > cur)
			time += (to - cur) * 6;
		else 
			time += (cur - to) * 4;
		time += 5;
		cur = to;
	}
	cout << time;
}
