/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/3
description:二叉堆
********************************************/
#include"binaryHeap.h"
#include <stdlib.h>
#include <iostream>


PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	if(MaxElements < 10)
	{
		fprintf(stderr,"too small elements\n");
		return NULL;
	}
	H = (PriorityQueue)malloc(sizeof(HeapStruct));
	if(H ==NULL)
	{
		fprintf(stderr,"out of space\n");
		return NULL;
	}
	H->capacity = MaxElements;
	H->size = 0;
	H->Elements = (ElementType *)malloc((MaxElements +1) *sizeof(ElementType));
	if(H ->Elements ==NULL)
	{
		fprintf(stderr,"out of space\n");
		return NULL;
	}
	H->Elements[0] = 0x80000000;
	return H;
}

void Destroy(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}

void makeEmpty(PriorityQueue H)
{
	H->size =0;
}

void Insert(ElementType X, PriorityQueue H)
{
	if(isFull(H))
		return;

	int i;
	i= ++ H->size ;
	while(H->Elements[i/2] > X)
	{
		H->Elements[i] = H->Elements[i/2];
		i = i/2;
	}
	H->Elements[i] = X;

}

ElementType DeleteMin(PriorityQueue H)
{
	if(isEmpty(H))
	{
		fprintf(stderr,"Queue is empty\n");
		return H->Elements[0];
	}

	ElementType min = H->Elements[1];
	ElementType last = H->Elements[H->size--];
	if(H->size == 0)
	{
		return min;
	}
	int i, child;
	for(i=1;;i = child)
	{
		/*书上的代码没有检查当size=1或者0的情况，这里先检查size是否为1*/
		if(2*i > H->size)
			break;

		child = 2*i;
		/*找到左右孩子中最小的一个，如果只有左孩子，就不会比较第二个选项*/
		if( child !=H->size && H->Elements[child]>H->Elements[child+1] )
			child++;

		/*最后一个元素和较小的孩子比较，小的放在空穴中*/
		if(last < H->Elements[child])
			break;

		H->Elements[i] = H->Elements[child];
	}
	H->Elements[i] = last;
	return min;

}

ElementType FindMin(PriorityQueue H)
{
	if(isEmpty(H))
	{
		fprintf(stderr,"Queue is empty\n");
		return H->Elements[0];
	}
	return H->Elements[1];
}

int isEmpty(PriorityQueue H)
{
	return H->size ==0;
}

int isFull(PriorityQueue H)
{
	return H->size == H->capacity;
}


void PercolateDown(PriorityQueue H, int hole)  
{  
    int i = 0;  
    int child = 0;  
    ElementType temp = 0;  
  
    if(NULL == H)  
    {  
        return;  
    }  
  
	temp = H->Elements[hole];  
    i = hole;  
    child = 2 * i;  
	while(child <= H->size)  
    {  
        if(child != H->size)    // have left+right child  
        {  
            if( H->Elements[child+1] < H->Elements[child])  
            {  
                child = child + 1;  
            }  
        }  
  
        // compare to h->ele[hole]  
        if(temp > H->Elements[child])  
        {  
            H->Elements[i] = H->Elements[child];  
        }  
        else  
        {  
            break;  
        }  
  
        i = child;  
        child = 2 * i;  
    }  
    H->Elements[i] = temp;  
} 

void PercolateUp(PriorityQueue H, int hole)  
{  
    int i = hole;  
    int parent = 0;  
    ElementType temp = H->Elements[hole];  
  
    parent = i >> 1;  
    while(temp < H->Elements[parent])  
    {  
        H->Elements[i] = H->Elements[parent];  
        i = parent;  
        parent = i >> 1;  
    }  
   H->Elements[i] = temp;  
}  

PriorityQueue BuildHeap(ElementType *x, int n)  
{  
    PriorityQueue H = NULL;  
    int i = 0;  
  
    H = Initialize(n);      /* include ele[0]=最小值 */  
    for(i=0; i<n; i++)  
    {  
        H->Elements[i+1] = x[i];  
    }  
  
	H->size = n;  
    for(i=n/2; i>0; i--)  
    {  
        PercolateDown(H, i);          
    }  
  
    return H;  
} 





void printDapth(ElementType X, int depth)
{
	while(depth >0)
	{
		printf("    ");
		depth--;
	}
	printf("%d\n", X);
}

void printBHeap(PriorityQueue H, int depth, int Index)
{
	if(Index <= H->size)
	{
		printBHeap(H, depth +1, 2*Index);
		printDapth(H->Elements[Index], depth);
		printBHeap(H, depth +1, 2*Index+1);
	}
}