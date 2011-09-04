#include<cmath>
#include<iostream>
using namespace std;

int  phi(int n)
{
	int ans,i,sq;
	ans=n;
	sq=(int)(sqrt((double) n));
	
	if(n%2==0)
		ans-=ans/2;
	while(n%2==0)
		n/=2;
		
	for(i=3;n>1 && i<=sq;++i)
		if(n%i==0)
		{
			ans-=ans/i;
			while(n%i==0)
				n/=i;
		}
	
	if(n>1)
		ans-=ans/n;
	return ans;
	
}

int main()
{
	int a;
	for(a=1;a<100;++a)
	{
		cout<<phi(a)<<endl;
	}
	return 0;
}