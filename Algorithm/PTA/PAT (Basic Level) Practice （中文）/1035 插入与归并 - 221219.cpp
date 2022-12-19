// 普通做法：单独写两种算法重新排序
#include <stdio.h>
#include <algorithm>

void insertSort(int a[], int e)
{
	// e - 新元素位置 
	// 插入排序是操作已排序的数组，所以从后往前移动元素
    int v = a[e], i = e - 1;
    for (; i >= 0 && a[i] > v; i--)
    {
        a[i + 1] = a[i];
        a[i] = v;
    }
}

void mergeSort(int a[], int n, int m)
{
    // m - 分组大小
    // 偷懒用 algorithm sort
    if (m > n)
        m = n;
    // 每 m 个元素划为一组，进行排序 
    for (int i = 0; i < n / m; i++)
        std::sort(a + i * m, a + (i + 1) * m);
    // 数组大小非m倍数时，最后一部分会有小于m个元素未排序 
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
    int n, org[100], a[100], b[100], res[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &org[i]), a[i] = b[i] = org[i];
    for (int i = 0; i < n; i++)
        scanf("%d", &res[i]);
    int m = 1;
    for (int i = 1; i < n; i++)
    {
        // i 从 1 开始，否则部分情况下会和使用归并排序过程中出现顺序一致 
        insertSort(a, i);
        if (compArray(a, res, n) == 0)
        {
        	// 注意，再进行一次排序时应对数组二进行操作，下同 
            printf("Insertion Sort\n");
            if (i + 1 < n)
                insertSort(res, i + 1);
            break;
        }
        
        // 归并排序 - 每一轮的分组大小需翻一倍 
        m *= 2;
        mergeSort(b, n, m);
        if (compArray(b, res, n) == 0)
        {
            printf("Merge Sort\n");
            mergeSort(res, n, m * 2);
            break;
        }
    }
    for (int i = 0; i < n; i++)
        printf(" %d" + !i, res[i]);
    printf("\n");
}
