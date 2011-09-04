/********************************************************************************************************************************

						MAX - PRIORITY QUEUE
							written by U.Swarnaprakash
						
						max_heap< Type >   Type - template
						Member Functions :
							maximum()  returns the maximum assuming heap is not empty
							pop_max()  pops the maximum and returns it assuming heap is not empty
							insert(Type)  inserts an element into the heap
						
						For user defined data types overload  the operator >  

************************************************************************************************************************************/



#include<iostream>
#include<cstdio>

using namespace std;

#define M 1005

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
class max_heap
{
	Type list[M];
	int heap_size;
	
public:
	max_heap()
	{
		heap_size=0;
	}
	void max_heapify(int);
	void make_max_heap(const Type *,int);
	Type maximum();
	Type pop_max();
	void increase_key(int,const Type &);
	void insert(const Type &);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void max_heap<Type>::max_heapify(int pos)
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void max_heap<Type>::make_max_heap(const Type *x,int size)
{
	int i;
	heap_size=size;
	
	for(i=0;i<heap_size;++i)
		list[i]=x[i];
		
	for(i=heap_size/2-1;i>=0;--i)
		max_heapify(i);
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
Type max_heap<Type>::maximum()
{
	return list[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
Type max_heap<Type>::pop_max()
{
	Type ans=list[0];
	list[0]=list[heap_size-1];
	--heap_size;
	max_heapify(0);
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void max_heap<Type>::increase_key(int pos,const Type &x)
{
	list[pos]=x;
	int p_pos;
	while(pos>0)
	{
		p_pos=parent(pos);
		if(list[pos]>list[p_pos])
		{
			my_swap(list[pos],list[p_pos]);
			pos=p_pos;
		}
		else
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void max_heap<Type>::insert(const Type &x)
{
	++heap_size;
	increase_key(heap_size-1,x);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	
	max_heap<int> h;
	
	int x;
	while(cin>>x)
	{
	
		h.insert(x);
		cout<<h.maximum()<<endl;
	}
	return 0;
}
