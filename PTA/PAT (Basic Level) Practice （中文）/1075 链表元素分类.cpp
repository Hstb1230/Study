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
	// 负数的头和尾
	int low_beg = -1, low_end = -1;
	// 0~K的头和尾
	int mid_beg = -1, mid_end = -1;
	// >K的头和尾
	int high_beg = -1, high_end = -1;
	
	int next;
	for(int i = start_addr; i != -1; i = next)
	{
		next = m[i].next;
		m[i].next = -1;
		
		if(m[i].value < 0)
		{
			// 没有负数链
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
			// 没有mid链
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
			// 没有K链
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
    // K链向前迁移(合并)
	if(mid_end == -1)
	{
		mid_beg = high_beg;
		mid_end = high_end;
	}
	else
	{
		m[mid_end].next = high_beg;
	}
    // 中链向前迁移
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
