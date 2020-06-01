#include <iostream>
using namespace std;

void printArr(int v[], int n)
{
	for(int i = n - 1; i >= 0; i--)
	{
		if(v[i] < 2) continue;
		printf("%d %d\n", i, v[i]);
	}
}

int main()
{
	int n;
	cin >> n;
	int v[n] = {0};
	int num;
	for(int i = 1; i <= n; i++)
	{
		cin >> num;
		v[(num > i ? num - i : i - num)]++;
	}
	printArr(v, n);
}
