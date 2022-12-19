// ��ͨ����������д�����㷨��������
#include <stdio.h>
#include <algorithm>

void insertSort(int a[], int e)
{
	// e - ��Ԫ��λ�� 
	// ���������ǲ�������������飬���ԴӺ���ǰ�ƶ�Ԫ��
    int v = a[e], i = e - 1;
    for (; i >= 0 && a[i] > v; i--)
    {
        a[i + 1] = a[i];
        a[i] = v;
    }
}

void mergeSort(int a[], int n, int m)
{
    // m - �����С
    // ͵���� algorithm sort
    if (m > n)
        m = n;
    // ÿ m ��Ԫ�ػ�Ϊһ�飬�������� 
    for (int i = 0; i < n / m; i++)
        std::sort(a + i * m, a + (i + 1) * m);
    // �����С��m����ʱ�����һ���ֻ���С��m��Ԫ��δ���� 
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
        // i �� 1 ��ʼ�����򲿷�����»��ʹ�ù鲢��������г���˳��һ�� 
        insertSort(a, i);
        if (compArray(a, res, n) == 0)
        {
        	// ע�⣬�ٽ���һ������ʱӦ����������в�������ͬ 
            printf("Insertion Sort\n");
            if (i + 1 < n)
                insertSort(res, i + 1);
            break;
        }
        
        // �鲢���� - ÿһ�ֵķ����С�跭һ�� 
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
