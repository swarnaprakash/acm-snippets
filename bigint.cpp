/***********************************************************************************************************************************
								ARBITRARY PRECISION ARITHMETIC
									written by U.Swarnaprakash

************************************************************************************************************************************/
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

/************************************************************************************************************************************/

struct bigint
{
	char digit[100];
	int length;
	
	
	bigint();
	bigint(int);
	bigint(long long);
	bigint(char *);
	bigint(string);
	
	void print();
	
	bigint operator+(bigint);
	bigint operator-(bigint);
	bigint operator*(bigint);
	bigint operator/(int);
	bigint operator/(long long);
	int operator%(int);
	long long operator%(long long);
	
	bool operator==(bigint);
	bool operator!=(bigint);
	bool operator<=(bigint);
	bool operator>(bigint);
	bool operator>=(bigint);
	bool operator<(bigint);
	
	friend ostream & operator<<(ostream &,bigint);
	
	operator int();
	operator long long();
	operator string();
};
/************************************************************************************************************************************/




/************************************************************************************************************************************/
bigint::bigint()
{
	length=0;
}

/************************************************************************************************************************************/
bigint::bigint(int n)
{
	int pos=0;
	
	while(n!=0)
	{
		digit[pos++]=n%10;
		n/=10;
	}
	
	length=pos;
}

/************************************************************************************************************************************/
bigint::bigint(long long n)
{
	int pos=0;
	
	while(n!=0)
	{
		digit[pos++]=n%10;
		n/=10;
	}
	
	length=pos;
}

/************************************************************************************************************************************/
bigint::bigint(char *n)
{
	int pos,len;
	
	length=len=strlen(n);
	pos=0;
	
	while(len--)
		digit[pos++]=n[len]-'0';
		
	for(pos=length-1;pos>=0 && digit[pos]==0;--pos);
	
	length=pos+1;
}

/************************************************************************************************************************************/
bigint::bigint(string n)
{
	int pos,len;
	
	length=len=n.size();
	pos=0;
	
	while(len--)
		digit[pos++]=n[len]-'0';
		
	for(pos=length-1;pos>=0 && digit[pos]==0;--pos);
	
	length=pos+1;
}

/************************************************************************************************************************************/
void bigint::print()
{
	int i;
	
	if(length==0)
		putchar('0');
	for(i=length-1;i>=0;--i)
		putchar(digit[i]+'0');
}

/************************************************************************************************************************************/
bigint bigint::operator+(bigint x)
{
	int i,carry,d;
	bigint aaa,bbb,result;

	if(length>x.length)
	{
		aaa=*this;
		bbb=x;
	}
	else
	{
		aaa=x;
		bbb=*this;
	}
	
	carry=0;
	for(i=0;i<bbb.length;++i)
	{
		d=aaa.digit[i]+bbb.digit[i]+carry;
		result.digit[i]=d%10;
		carry=d/10;
	}
	for(;i<aaa.length;++i)
	{
		d=aaa.digit[i]+carry;
		result.digit[i]=d%10;
		carry=d/10;
	}
	
	if(carry!=0)
		result.digit[i++]=carry;
		
	result.length=i;
	return result;
}

/************************************************************************************************************************************/
bigint bigint::operator-(bigint x)
{
	int i,borrow,d;
	bigint result;
	
	borrow=0;
	for(i=0;i<x.length;++i)
	{
		d=digit[i]-x.digit[i]-borrow;
		if(d<0)
		{
			result.digit[i]=d+10;
			borrow=1;
		}
		else
		{
			result.digit[i]=d;
			borrow=0;
		}
	}
	
	for(;i<length;++i)
	{
		d=digit[i]-borrow;
		if(d<0)
		{
			result.digit[i]=d+10;
			borrow=1;
		}
		else
		{
			result.digit[i]=d;
			borrow=0;
		}
	}
	
	for(i=length-1;i>=0 && result.digit[i]==0;--i);
	
	result.length=i+1;
	return result;
}

/************************************************************************************************************************************/
bigint bigint::operator*(bigint x)
{
	int r,i,j,hi,lo,carry,tmp;
	bigint result;
	
	r=length+x.length-1;
	carry=0;
	
	for(i=0;i<r;++i)
	{
		lo=0;hi=i+1;
		
		if(hi>length)
			hi=length;
		if((i-lo)>=x.length)
			lo=i-x.length+1;
		
		tmp=carry;
		for(j=lo;j<hi;++j)
			tmp+=digit[j]*x.digit[i-j];
		
		result.digit[i]=tmp%10;
		carry=tmp/10;
	}
	
	if(carry!=0)
		result.digit[i++]=carry;
	
	result.length=i;
	for(i=result.length-1;i>=0 && result.digit[i]==0;--i);

	result.length=i+1;
	return result;
}

/************************************************************************************************************************************/
bigint bigint::operator/(int x)
{
	bigint result;
	int i;
	int tmp,n;
	
	n=0;
	for(i=length-1;i>=0;--i)
	{
		tmp=n*10+digit[i];
		if(tmp>=x)
			break;
		n=tmp;
	}
	
	result.length=i+1;
	for(;i>=0;--i)
	{
		n*=10;
		n+=digit[i];
		result.digit[i]=n/x;
		n%=x;
	}
	return result;
}

/************************************************************************************************************************************/

bigint bigint::operator/(long long x)
{
	bigint result;
	int i;
	long long tmp,n;
	
	n=0;
	for(i=length-1;i>=0;--i)
	{
		tmp=n*10+digit[i];
		if(tmp>=x)
			break;
		n=tmp;
	}
	
	result.length=i+1;
	for(;i>=0;--i)
	{
		n*=10;
		n+=digit[i];
		result.digit[i]=n/x;
		n%=x;
	}
	return result;
}

/************************************************************************************************************************************/
int bigint::operator%(int x)
{
	int result=0;
	int i;
	for(i=length-1;i>=0;--i)
		result=(result*10+digit[i])%x;
	return result;
}

/************************************************************************************************************************************/
long long bigint::operator%(long long x)
{
	long long result=0;
	int i;
	for(i=length-1;i>=0;--i)
		result=(result*10+digit[i])%x;
	return result;
}

/************************************************************************************************************************************/
bool bigint::operator==(bigint x)
{
	int i;
	
	if(length!=x.length)
		return false;
	for(i=0;i<length;++i)
		if(digit[i]!=x.digit[i])
			return false;
	return true;
}

/************************************************************************************************************************************/
bool bigint::operator!=(bigint x)
{
	int i;
	
	if(length!=x.length)
		return true;
	for(i=0;i<length;++i)
		if(digit[i]!=x.digit[i])
			return true;
	return false;
}

/************************************************************************************************************************************/
bool bigint::operator<=(bigint x)
{
	int i;
	
	if(length!=x.length)
		return length<x.length;
		
	for(i=length-1;i>=0;--i)
		if(digit[i]!=x.digit[i])
			return digit[i]<x.digit[i];
	
	return true;
}

/************************************************************************************************************************************/
bool bigint::operator>(bigint x)
{
	int i;
	
	if(length!=x.length)
		return length>x.length;
		
	for(i=length-1;i>=0;--i)
		if(digit[i]!=x.digit[i])
			return digit[i]>x.digit[i];
	
	return false;
}

/************************************************************************************************************************************/
bool bigint::operator>=(bigint x)
{
	int i;
	
	if(length!=x.length)
		return length>x.length;
	
	for(i=length-1;i>=0;--i)
		if(digit[i]!=x.digit[i])
			return digit[i]>x.digit[i];
			
	return true;
}

/************************************************************************************************************************************/
bool bigint::operator<(bigint x)
{
	int i;
	
	if(length!=x.length)
		return length<x.length;
	
	for(i=length-1;i>=0;--i)
		if(digit[i]!=x.digit[i])
			return digit[i]<x.digit[i];
			
	return false;
}

/************************************************************************************************************************************/
ostream & operator<<(ostream &bout,bigint x)
{
	int i;
	
	if(x.length==0)
		bout<<0;
	for(i=x.length-1;i>=0;--i)
		bout<<(char)(x.digit[i]+'0');
	return bout;
}

/************************************************************************************************************************************/
bigint::operator int()
{
	int result=0;
	int i;
	for(i=length-1;i>=0;--i)
	{
		result*=10;
		result+=digit[i];
	}
	return result;
}

/************************************************************************************************************************************/
bigint::operator long long()
{
	long long result=0;
	int i;
	for(i=length-1;i>=0;--i)
	{
		result*=10;
		result+=digit[i];
	}
	return result;
}

/************************************************************************************************************************************/
bigint::operator string()
{
	string result;
	int i;
	for(i=length-1;i>=0;--i)
		result+=digit[i]+'0';
	return result;
}

/************************************************************************************************************************************/
int main()
{
	string x,y;
	long long n;
	while(cin>>x>>y)
	{
		
		//bigint b(y);
		
		cout<<bigint(x)+bigint(y)<<endl;
	}
	return 0;
}
/************************************************************************************************************************************/
