#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_array(vector<int> v, int vaild_count)
{
	printf("%d |", vaild_count);
	for(int i = 0; i < vaild_count; i++)
		printf(" %d", v[i]);
	printf("\n");
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
    vector<int> v;
    int vaild_count;
    double g1, g2;
	for(int i = 0; i < n; i++)
	{
		vaild_count = 0;
		v.resize(n);
		for(int j = 0; j < n; j++)
		{
			scanf("%d", &v[vaild_count]);
			if(v[vaild_count] >= 0 && v[vaild_count] <= m)
				vaild_count++;
		}
		g1 = v[0];
		sort(&v[1], &v[vaild_count]);
//		print_array(v, vaild_count);
		g2 = 0;
		for(int k = 2; k < vaild_count - 1; k++)
		{
			g2 += v[k];
		}
		g2 /= vaild_count - 3;
//		printf("%d %.2f %.2f\n", vaild_count, g1, g2);
		printf("%d\n", int((g1 + g2) / 2 + 0.5));
	}
}
