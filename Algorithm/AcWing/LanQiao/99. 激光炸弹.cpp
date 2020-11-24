#include <iostream>
#include <cstdio>

using namespace std;

const int N = 5010;

int a[N][N], s[N][N];

int n, r;

int main()
{
    scanf("%d%d", &n, &r);
    int x, y;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x, &y);
        scanf("%d", &a[x][y]);
    }
}
