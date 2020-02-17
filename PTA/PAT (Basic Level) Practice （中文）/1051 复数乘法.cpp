#include <iostream>
#include <cmath>
using namespace std;

int main() {
	double r1, p1, r2, p2;
	cin >> r1 >> p1 >> r2 >> p2;
	double a, b, c, d;
	a = r1 * cos(p1);
	b = r1 * sin(p1);
	c = r2 * cos(p2);
	d = r2 * sin(p2);
	double re = a * c - b * d;
	double im = b * c + a * d;
	if(fabs(re) < 0.01) re = 0;
	if(fabs(im) < 0.01) im = 0;
	if(im < 0)
		printf("%.2lf%.2lfi", re, im);
	else
		printf("%.2lf+%.2lfi", re, im);
}
