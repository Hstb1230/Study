#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> w;

int main()
{
    cin >> n >> m;
    int u = 0;
    while(m > 0)
    {
        if(w.size() == m)
        {
            for(auto it : w)
                printf("%d ", it + 1);
            puts("");
            // ÅÐ¶ÏÊÇ·ñ³ö±ß½ç
			do
            {
                u = w.back();
                w.pop_back();
            } while(u + 1 >= n || (u + m - w.size() >= n && w.size() > 0));
			if(w.size() == 0 && n - (u + 1) < m)
   				break;
			u++;
            continue;
        }
        w.push_back(u);
        u++;
    }
}
