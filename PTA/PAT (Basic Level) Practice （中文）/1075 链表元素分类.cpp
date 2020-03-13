#include <iostream>
#include <map>
using namespace std;

struct node
{
	int value;
	int next;
};

map<int, node> m;

void print_map(int beg)
{
//	printf("%d", m[beg].value);
//	for(int i = m[beg].next; i != -1; i = m[i].next)
//	{
//		printf(" -> %d", m[i].value);
//	}
	for(int i = beg; i != -1; i = m[i].next)
	{
		printf("%05d %d ", i, m[i].value);
		if(m[i].next == -1)
			printf("-1\n");
		else
			printf("%05d\n", m[i].next);
	}
}

int main()
{
	int start_addr, node_count, k;
	scanf("%d%d%d", &start_addr, &node_count, &k);
	int addr;
	for(int i = 0; i < node_count; i++)
	{
		scanf("%d", &addr);
		scanf("%d%d", &m[addr].value, &m[addr].next);
	}
	// ������ͷ��β
	int low_beg = -1, low_end = -1;
	// 0~K��ͷ��β
	int mid_beg = -1, mid_end = -1;
	// >K��ͷ��β
	int high_beg = -1, high_end = -1;
	
	int next;
	for(int i = start_addr; i != -1; i = next)
	{
		next = m[i].next;
		m[i].next = -1;
		
		if(m[i].value < 0)
		{
			// û�и�����
			if(low_end == -1)
			{
				low_end = low_beg = i;
			}
			else
			{
				m[low_end].next = i;
				low_end = i;
			}
//			printf("low [%d]%d\n", i, m[i].value);
		}
		else if(m[i].value <= k)
		{
			// û��mid��
			if(mid_end == -1)
			{
				mid_end = mid_beg = i;
			}
			else
			{
				m[mid_end].next = i;
				mid_end = i;
			}
//			printf("mid [%d]%d\n", i, m[i].value);
		}
		else // > K
		{
			// û��K��
			if(high_end == -1)
			{
				high_end = high_beg = i;
			}
			else 
			{
				m[high_end].next = i;
				high_end = i;
			}
//			printf("high [%d]%d\n", i, m[i].value);
		}
	}
//	printf("low[%d, %d]\n", low_beg, low_end);
//	printf("mid[%d, %d]\n", mid_beg, mid_end);
//	printf("high[%d, %d]\n", high_beg, high_end);
    // K����ǰǨ��(�ϲ�)
	if(mid_end == -1)
	{
		mid_beg = high_beg;
		mid_end = high_end;
	}
	else
	{
		m[mid_end].next = high_beg;
	}
    // ������ǰǨ��
    if(low_end == -1)
    {
    	low_beg = mid_beg;
    	low_end = mid_end;
	}
	else
	{
		m[low_end].next = mid_beg;
	}
	print_map(low_beg);
}
