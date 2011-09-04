/***********************************************************************************************************************************
									         FRACTION CLASS
									written by U.Swarnaprakash

************************************************************************************************************************************/

#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<sstream>

using namespace std;

/************************************************************************************************************************************/

typedef long long type;

template<class T>
T gcd(T m, T n)
{
	T rem;
	while(n>0)
	{
		rem=m%n;
		m=n;
		n=rem;
	}
	return m;
}

template<class T>
T lcm(T m,T n)
{
	return m/gcd(m,n)*n;
}

/************************************************************************************************************************************/

class fraction
{
	public:
	type num,den;
	
	fraction();
	fraction(int,int);
	fraction(long long,long long);
	fraction operator+(fraction);
	fraction operator-(fraction);
	fraction operator*(fraction);
	fraction operator/(fraction);
	bool operator<(fraction);
	bool operator>(fraction);
	bool operator<=(fraction);
	bool operator>=(fraction);
	bool operator==(fraction);
	bool operator!=(fraction);
	
	operator string();
	operator double();
	
	void reduce();
	void print();
	
};
/************************************************************************************************************************************/



/************************************************************************************************************************************/
fraction::fraction()
{
	num=0;
	den=1;
}

/************************************************************************************************************************************/
fraction::fraction(int x,int y)
{
	int hcf=gcd(x,y);
	x/=hcf;
	y/=hcf;
	num=x;
	den=y;
}

/************************************************************************************************************************************/
fraction::fraction(long long x,long long y)
{
	int hcf=gcd(x,y);
	x/=hcf;
	y/=hcf;
	num=x;
	den=y;
}

/************************************************************************************************************************************/
fraction fraction::operator+(fraction x)
{
	fraction ans;
	ans.den=lcm(den,x.den);
	ans.num=num*(ans.den/den)+x.num*(ans.den/x.den);
	type hcf=gcd(ans.num,ans.den);
	ans.num/=hcf;
	ans.den/=hcf;
	return ans;
}

/************************************************************************************************************************************/
fraction fraction::operator-(fraction x)
{
	//assuming operand 1 is greater than operand 2
	fraction ans;
	ans.den=lcm(den,x.den);
	ans.num=num*(ans.den/den)-x.num*(ans.den/x.den);
	type hcf=gcd(ans.num,ans.den);
	ans.num/=hcf;
	ans.den/=hcf;
	return ans;
}

/************************************************************************************************************************************/
fraction fraction::operator*(fraction x)
{
	type hcf;
	fraction y=*this;
	
	hcf=gcd(y.num,x.den);
	y.num/=hcf;
	x.den/=hcf;
	
	hcf=gcd(x.num,y.den);
	x.num/=hcf;
	y.den/=hcf;
	
	fraction ans;
	ans.num=y.num*x.num;
	ans.den=y.den*x.den;
	return ans;
}

/************************************************************************************************************************************/
fraction fraction::operator/(fraction x)
{

	swap(x.num,x.den);
	type hcf;
	fraction y=*this;
	
	hcf=gcd(y.num,x.den);
	y.num/=hcf;
	x.den/=hcf;
	
	hcf=gcd(x.num,y.den);
	x.num/=hcf;
	y.den/=hcf;
	
	fraction ans;
	ans.num=y.num*x.num;
	ans.den=y.den*x.den;
	return ans;
}

/************************************************************************************************************************************/
bool fraction::operator<(fraction x)
{
	type LCM=lcm(den,x.den);
	return ((num*(LCM/den))<(x.num*(LCM/x.den)));
}

/************************************************************************************************************************************/
bool fraction::operator>(fraction x)
{
	type LCM=lcm(den,x.den);
	return ((num*(LCM/den))>(x.num*(LCM/x.den)));
}

/************************************************************************************************************************************/
bool fraction::operator<=(fraction x)
{
	type LCM=lcm(den,x.den);
	return ((num*(LCM/den))<=(x.num*(LCM/x.den)));
}

/************************************************************************************************************************************/
bool fraction::operator>=(fraction x)
{
	type LCM=lcm(den,x.den);
	return ((num*(LCM/den))>=(x.num*(LCM/x.den)));
}

/************************************************************************************************************************************/
bool fraction::operator==(fraction x)
{
	type LCM=lcm(den,x.den);
	return ((num*(LCM/den))==(x.num*(LCM/x.den)));
}

/************************************************************************************************************************************/
bool fraction::operator!=(fraction x)
{
	type LCM=lcm(den,x.den);
	return ((num*(LCM/den))!=(x.num*(LCM/x.den)));
}

/************************************************************************************************************************************/
fraction::operator string()
{
	stringstream ss;
	ss<<num<<"/"<<den;
	return ss.str();
}

/************************************************************************************************************************************/
fraction::operator double()
{
	return (double)num/(double)den;
}

/************************************************************************************************************************************/
void fraction::reduce()
{
	type hcf=gcd(num,den);
	num/=hcf;
	den/=hcf;
}

/************************************************************************************************************************************/
void fraction::print()
{
	//printf("%lld/%lld",num,den);
	cout<<num<<"/"<<den;
}

/************************************************************************************************************************************/
int main()
{

	fraction onefour(1,4);
	onefour.print();
	while(1)
	{
	type x,y;
	cin>>x>>y;
	fraction a(x,y);
	cin>>x>>y;
	fraction b(x,y);
	
	(a*b).print();
	
	puts("");
	}
	return 0;
}

/************************************************************************************************************************************/
