#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	int cnt;
	vector<int> a(n, 0);
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cin >> cnt;
			a[j] += cnt;
		}
	}
	vector<int> r(0);
	int max = a[0];
	for(int i = 0; i < a.size(); i++)
	{
		if(a[i] > max)
		{
			max = a[i];
			r.clear();
			r.push_back(i + 1);
		}
		else if(a[i] == max)
			r.push_back(i + 1);
	}
	cout << max << endl;
	for(int i = 0; i < r.size(); i++)
	{
		if(i > 0) cout << " ";
		cout << r[i];
	}
	
}
