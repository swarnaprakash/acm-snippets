#include<iostream>
#include<cstdio>

using namespace std;

// solves d=gcd(a,b)=ax+by
//when a and b are coprime,x is the modular multiplicative inverse of a modulo b.
void extended_euclid(int a,int b,int &d,int &x,int &y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		int d1,x1,y1;
		extended_euclid(b,a%b,d1,x1,y1);
		d=d1;
		x=y1;
		y=x1-(a/b)*y1;
	}
}

int main()
{
	int a,b,gcd,x,y;
	cin>>a>>b;
	extended_euclid(a,b,gcd,x,y);
	cout<<x<<" "<<y;
	return 0;
}
