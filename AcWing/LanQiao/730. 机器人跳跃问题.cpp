#include <iostream>
using namespace std;

const int N = 100010;
int n, h[N];

typedef long long ll;

bool check(ll e)
{
    for(int i = 0; i < n; i++)
    {
        e += e - h[i];
        if(e < 0) return false;
        else if(e >= 1e5) break;
    }
    return true;
}

int main()
{
    cin >> n;
    int l = 1e5, r = -1e5;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &h[i]);
        if(h[i] < l) l = h[i];
        if(h[i] > r) r = h[i];
    }
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l;
}
