// https://www.liuchuo.net/archives/503
#include <stdio.h>
#include <algorithm>

void insertSort(int a[], int e)
{
    int v = a[e], i = e - 1;
    for (; i >= 0 && a[i] > v; i--)
    {
        a[i + 1] = a[i];
        a[i] = v;
    }
}

void mergeSort(int a[], int n, int m)
{
	// 偷懒用 algorithm sort 
    // m - 分组大小
    if (m > n)
        m = n;
    for (int i = 0; i < n / m; i++)
        std::sort(a + i * m, a + (i + 1) * m);
    std::sort(a + n / m * m, a + n);
}

int compArray(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 1;
    }
    return 0;
}

int main()
{
    int n, org[100], mid[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &org[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &mid[i]);
    // 判断是否为插入排序
	// 前面部分是递增的，后面部分与原数组一致 
    int i, j;
    for (i = 0; i < n - 1 && mid[i] <= mid[i + 1]; i++);
    for (j = i + 1; j < n && mid[j] == org[j]; j++);
    if (j == n)
    {
        printf("Insertion Sort\n");
        insertSort(mid, i + 1);
    }
    else
    {
    	// 归并排序只能从头开始，因为分组大小是未知的 
        printf("Merge Sort\n");
        for (int m = 1; m <= n; m *= 2)
        {
            mergeSort(org, n, m);
            if (compArray(org, mid, n) == 0)
            {
                mergeSort(mid, n, m * 2);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++)
        printf(" %d" + !i, mid[i]);
    printf("\n");
}
