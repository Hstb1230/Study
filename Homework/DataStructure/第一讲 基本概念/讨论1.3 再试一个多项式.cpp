#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

#define count 10000

void f1(double & x)
{
	double r = 1;
	for(int i = 1; i <= 100; i++)
		r += pow(x, i) / i;
}

void f2(double & x)
{
	double r = 0;
	for(int i = 100; i > 0; i--)
		r = x * (1.0 / i + r);
	r += 1;
}

int main()
{
	double x = 1.1;
	clock_t begin, end;
	int n;
	for(auto f : {f1, f2})
	{
		n = count;
		begin = clock();
		while(n--)
			f(x);
		end = clock();
		cout << (double(end - begin) / CLK_TCK) << endl;
	}
}
