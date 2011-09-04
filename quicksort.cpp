/********************************************************************************************************************************

						QUICK SORT
							written by U.Swarnaprakash
						
						Arguments similar to sort() in STL
						quicksort(A,A+n) sorts elements in the range [A,A+n)
						
						For user defined data types overload  the operator <  

************************************************************************************************************************************/



#include<iostream>
#include<cstdio>

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
inline void my_swap(Type &a,Type &b)
{
	Type x;
	x=a;
	a=b;
	b=x;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void quicksort(Type *start,Type *end)
{
	int length=end-start;
	
	if(length<2)
		return;
	
	if(length==2)  // this is necessary as the value right-2 will take negative values for length =2
	{
		if(start[1]<start[0])
			my_swap(start[0],start[1]);
		return;
	}
	
	
// Median of Three Partitioning ...
	int left,right,center;
	left=0;
	right=length-1;
	center=(left+right)>>1;
	
	if( start[center]<start[left] )
		my_swap(start[center],start[left]);
	if( start[right]<start[left] )
		my_swap(start[right],start[left]);
	if( start[right]<start[center] )
		my_swap(start[right],start[center]);

/*
Left ,right,Center are sorted and hence center is the median of the three .Now the maximum element is in the right which is the correct position.So we place the pivot in right-1  and start from left+1 and right-2 and compare with the pivot.

*/
	my_swap(start[right-1],start[center]); 

	Type pivot = start[right-1];
	
	int i,j;
	i=left;
	j=right-1;
	
	// i and j values wont go out of array bounds  since left and pivot(in right) would act as Sentinels
	while(1)
	{
		for(++i;start[i]<pivot;++i);
		for(--j;pivot<start[j];--j);
		if(i<j)
			my_swap(start[i],start[j]);
		else
			break;
	}
	
	swap(start[i],start[right-1]);	//Restore pivot to its position
	
	quicksort(start,start+i);
	quicksort(start+i,end);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int a[100005];
	int n,i;
	clock_t st,en;
	
	while(cin>>n)
	{
		for(i=0;i<n;++i)
			cin>>a[i];
		
		st=clock();
		quicksort(a,a+n);
		en=clock();
		
		for(i=0;i<n;++i)
			cout<<a[i]<<" ";
	
		cout<<endl;
	}
	double rt=(double)(en-st)/CLOCKS_PER_SEC;
	cout<<rt;
	
	return 0;
}

/*
For a list of 10^5 integers sorting algorithms take the following times to sort ALONE  (tested on identical conditions and test data)

MergeSort	0.120 s
HeapSort	0.073 s
QuickSort	0.033 s
*/

