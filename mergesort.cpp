/********************************************************************************************************************************

						MERGE SORT
							written by U.Swarnaprakash
						
						Arguments similar to sort() in STL
						mergesort(A,A+n) sorts elements in the range [A,A+n)
						
						For user defined data types overload  the operator <  

************************************************************************************************************************************/



#include<iostream>
#include<cstdio>
#include<ctime>

using namespace std;

template<class Type>
void mergesort(Type *,Type *);
template<class Type>
void merge(Type *,Type *,Type *,int,int);
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
		mergesort(a,a+n);
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void mergesort(Type *start,Type *end)
{
	int length=end-start;
	if(length<=1)
		return;
	
	int A_length=length/2;
	int B_length=length - A_length;
	
	Type *List_A = new Type [A_length];
	Type *List_B = new Type [B_length];
	
	int i;
	for(i=0;i<A_length;++i)
		List_A[i]=*(start+i);
	for(i=A_length;i<length;++i)
		List_B[i-A_length]=*(start+i);
	
	mergesort(List_A , List_A + A_length);
	mergesort(List_B , List_B + B_length);
	merge(start,List_A,List_B,A_length,B_length);
	
	delete []List_A;
	delete []List_B;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void merge(Type *X,Type *List_A,Type *List_B,int A_length,int B_length)
{
	int pos1,pos2;
	pos1=pos2=0;
	
	while(pos1<A_length && pos2<B_length)
	{
		if(List_B[pos2]<List_A[pos1])
		{
			*X=List_B[pos2];
			++pos2;
		}
		else
		{
			*X=List_A[pos1];
			++pos1;
		}
		++X;
	}
	int i;
	for(i=pos1;i<A_length;++i)
	{
		*X=List_A[i];
		++X;
	}
	for(i=pos2;i<B_length;++i)
	{
		*X=List_B[i];
		++X;
	}
}
