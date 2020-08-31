#include <iostream>
using namespace std;

const int N = 100010;

struct
{
    int h, w;
} cc[N];

int n, k;

bool check(int e)
{
    int cnt = 0;
    for(int i = 0; i < n; i++)
        cnt += (cc[i].h * cc[i].w) / (e * e);
    return cnt >= k;
}

int main()
{
    scanf("%d%d", &n, &k);
    int l = 1, r = 1e5;
    for(int i = 0; i < n; i++)
        scanf("%d%d", &cc[i].h, &cc[i].w);
    while(l < r)
    {
        int mid = (l + r + 1) >> 1;
    	// 越小越容易划多份
        if(check(mid))
			// 能分到，增大面积
            l = mid;
        else
			// 分不到，缩小面积
            r = mid - 1;
    }
    cout << l;
}
