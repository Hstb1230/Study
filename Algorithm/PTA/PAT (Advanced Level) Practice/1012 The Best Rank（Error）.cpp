#include <iostream>
#include <map>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	int si, sc, sm, se, sa;                  // sc = score of x
	int mc = 0, mm = 0, me = 0, ma = 0;      // mx = max of x
	map<int, bool> vc[101], vm[101], ve[101], va[101], vi;
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d%d%d", &si, &sc, &sm, &se);
		sa = (sc + sm + se) / 3.0 + 0.5;
		vi[si] = true;
		vc[sc][si] = vm[sm][si] = ve[se][si] = va[sa][si] = true;
		if(sc > mc) mc = sc;
		if(sm > mm) mm = sm;
		if(se > me) me = se;
		if(sa > ma) ma = sa;
	}
	
	int rr = m, rt = 0, rc = 0; // result of rank, res of type
	char rts[] = "ACME";
	for(int i = 0; i < m; i++)
	{
		scanf("%d", &si);
		if(vi.count(si) == 0)
		{
			printf("N/A\n");
			continue;
		}

  		rr = m, rt = 0;

		// 判断 avg
		rc = 0;
		for(int t = ma; t >= 0; t--)
		{
			if(va[t].size() == 0)
				continue;
			if(va[t].count(si) > 0)
			{
				if(++rc < rr)
				{
					rr = rc;
					rt = 0;
				}
				break;
			}
			rc += va[t].size();
		}

		// 判断 c lang
		rc = 0;
		for(int t = mc; t >= 0; t--)
		{
			if(vc[t].size() == 0)
				continue;
			if(vc[t].count(si) > 0)
			{
				if(++rc < rr)
				{
					rr = rc;
					rt = 1;
				}
				break;
			}
			rc += vc[t].size();
		}

		// 判断 math
		rc = 0;
		for(int t = mm; t >= 0; t--)
		{
			if(vm[t].size() == 0)
				continue;
			if(vm[t].count(si) > 0)
			{
				if(++rc < rr)
				{
					rr = rc;
					rt = 2;
				}
				break;
			}
			rc += vm[t].size();
		}

		// 判断 english
		rc = 0;
		for(int t = me; t >= 0; t--)
		{
			if(ve[t].size() == 0)
				continue;
			if(ve[t].count(si) > 0)
			{
				if(++rc < rr)
				{
					rr = rc;
					rt = 3;
				}
				break;
			}
			rc += ve[t].size();
		}

		rp:
			printf("%d %c\n", rr, rts[rt]);
	}
}
