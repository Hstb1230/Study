#include <iostream>
#include <cstdio>

using namespace std;

const int N = 100010;

int n, k, ans;
int a[N], s[N];

int main()
{
    scanf("%d%d", &n, &k);

    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = i; j <= n; j++)
        {
            if((s[j] - s[i - 1]) % k == 0)
                ans++;
        }
    }

    printf("%d\n", ans);

    return 0;
}
