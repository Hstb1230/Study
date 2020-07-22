#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

/* 你的代码将被嵌在这里 */
List ReadInput()
{
	int n;
	scanf("%d", &n);
	List L;
	L->Last = n;
	int i;
	for(i = 1; i <= n; i++)
	    scanf("%d", &L->Data[i]);
	return L;
}

Position BinarySearch( List L, ElementType X )
{
	int beg = 1, end = L->Last;
	while(beg <= end)
	{
		int mid = (beg + end) / 2;
		if(L->Data[mid] == X)
			return mid;
		else if(L->Data[mid] > X)
			end = mid - 1;
		else
			beg = mid + 1;
	}
	return NotFound;
}
