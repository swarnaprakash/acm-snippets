/********************************************************************************************************************************

						HEAP SORT
							written by U.Swarnaprakash
						
						Arguments similar to sort() in STL
						heapsort(A,A+n) sorts elements in the range [A,A+n)
						
						For user defined data types overload  the operator >  

************************************************************************************************************************************/


#include<iostream>
#include<cstdio>
#include<ctime>

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int parent(int i)
{
	return ((i-1)>>1);
}

inline int left(int i)
{
	return ((i<<1)+1);
}

inline int right(int i)
{
	return ((i<<1)+2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void my_swap(Type &a,Type &b)
{
	Type x;
	x=a;
	a=b;
	b=x;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void max_heapify(Type *list,int pos,int heap_size)
{
	int lpos,rpos;
	int max_pos;
	
	while(1)
	{
		max_pos=pos;
		lpos=left(pos);
		rpos=right(pos);
		
		if(lpos<heap_size && list[lpos] > list[pos])
			max_pos=lpos;
		if(rpos<heap_size && list[rpos] > list[max_pos])
			max_pos=rpos;
			
		if(max_pos==pos)
			break;
		my_swap(list[pos],list[max_pos]);
		pos=max_pos;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void make_max_heap(Type *start,Type *end)
{
	int length=end-start;
	
	int i;
	for(i=length/2-1;i>=0;--i)
		max_heapify(start,i,length);
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void heapsort(Type *start,Type *end)
{
	make_max_heap(start,end);
	int heap_size=end-start;
	int i;
	for(i=heap_size-1;i>0;--i)
	{
		my_swap(start[0],start[i]);
		--heap_size;
		max_heapify(start,0,heap_size);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
main()
{
	int a[100005];
	int n,i;
	clock_t st,en;
	
	while(cin>>n)
	{
		for(i=0;i<n;++i)
			cin>>a[i];
		
		st=clock();
		heapsort(a,a+n);
		en=clock();
		
		for(i=0;i<n;++i)
			cout<<a[i]<<" ";
	
		cout<<endl;
	}
	double rt=(double)(en-st)/CLOCKS_PER_SEC;
	//cout<<rt;
	
	return 0;
}


/*
For a list of 10^5 integers sorting algorithms take the following times to sort ALONE  (tested on identical conditions and test data)

MergeSort	0.120 s
HeapSort	0.073 s
QuickSort	0.033 s
*/
