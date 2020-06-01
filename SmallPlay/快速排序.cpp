/*
	A simplified version of quick sort
*/
#include <iostream>
#include <vector>
using namespace std;

void qSort(vector<int> & v)
{
	if(v.size() < 2)
		return;
	int referIndex = 1;     		// 基准值下标
	int referValue = v[referIndex]; // 基准值
	vector<int> vSmall(0);
	vector<int> vLarge(0);
	for(int i = 0; i < v.size(); i++)
	{
		if(i == referIndex)
			continue;
		if(v[i] <= referValue)
			vSmall.push_back(v[i]);
		else
			vLarge.push_back(v[i]);
	}
	qSort(vSmall);
	qSort(vLarge);
	v.assign(vSmall.begin(), vSmall.end());
	v.push_back(referValue);
	v.insert(v.end(), vLarge.begin(), vLarge.end());
}

void printArray(vector<int> v)
{
	for(vector<int>::iterator i = v.begin(); i != v.end(); i++)
	{
		printf("%d ", *i);
	}
}

int main()
{
	int a[] = {1, 33, 4, 2, 5};
	vector<int> v(a, a + 5);
	qSort(v);
	printArray(v);
}
