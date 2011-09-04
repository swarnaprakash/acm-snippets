/**************************************************************************************************
Determinant of a matrix by Dynamic programming 
http://forums.topcoder.com/?module=Thread&threadID=513084&start=0&mc=15#559253

Time Complexity : O( n * 2^n)
Note: permanent is similar to determinant without + - signs....


**************************************************************************************************/
#include<iostream>
#include<cstdio>

using namespace std;

#define LL long long

LL determinant(LL **,int);

main()
{
	LL **a;
	int n;
	int i,j;
	cin>>n;
	
	a = new LL *[n];
	
	for(i=0;i<n;++i)
		a[i] = new LL[n];
	
	for(i=0;i<n;++i)
		for(j=0;j<n;++j)
			cin>>a[i][j];
			
	cout<<determinant(a,n);
	
	for(i=0;i<n;++i)
		delete a[i];
		
	delete a;
	
	return 0;
}

LL determinant(LL **mat,int n)
{
	int sz=1<<n;
	LL d[sz];
	d[0]=1;
	
	int bits_i; // number of 1 bits in i
	int i,j;
	
	for(i=1;i<sz;++i)
	{
		int tmp=i;
		bits_i=0;
		while(tmp>0)
		{
			bits_i++;
			tmp=tmp&(tmp-1);
		}
		int r = n- bits_i;
		
		d[i]=0;
		int sign=1;
					
		for(j=0;j<n;++j)
		{
			if(i&(1<<j)) // if jth bit is set 
			{
				int prev=i^(1<<j); // i with jth bit turned off  ==> without the column
				d[i]+=mat[r][j]*d[prev]*sign;
				sign*=-1;
			}
		}
	}
	
	return d[sz-1];
	
}