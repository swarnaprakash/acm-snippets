/***********************************************************************************************************************************
								ARBITRARY PRECISION ARITHMETIC
									written by U.Swarnaprakash

************************************************************************************************************************************/
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

#define BASE 10000
#define D 4

/************************************************************************************************************************************/

struct bigint
{
	int digit[100];
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
		digit[pos++]=n%BASE;
		n/=BASE;
	}
	
	length=pos;
}

/************************************************************************************************************************************/
bigint::bigint(long long n)
{
	int pos=0;
	
	while(n!=0)
	{
		digit[pos++]=n%BASE;
		n/=BASE ;
	}
	
	length=pos;
}

/************************************************************************************************************************************/
bigint::bigint(char *n)
{
	int pos,len;
	int i,j,tmp;
	int string_length=strlen(n);
	
	length=len=(string_length+D-1)/D;
	
	tmp=0;
	for(i=0;n[i]!=0 && i<string_length%D;++i)
	{
		tmp*=10;
		tmp+=n[i]-'0';
	}
	--len;
	if(i!=0)
	{
		digit[len]=tmp;
		--len;
	}
	
	for(;i<string_length;i+=D)
	{
		tmp=0;
		for(j=0;j<D;++j)
		{
			tmp*=10;
			tmp+=n[i+j]-'0';
		}
		digit[len]=tmp;
		--len;
	}
		
	for(pos=length-1;pos>=0 && digit[pos]==0;--pos);
	
	length=pos+1;
}

/************************************************************************************************************************************/
bigint::bigint(string n)
{
	int pos,len;
	int i,j,tmp;
	int string_length=n.size();
	
	length=len=(string_length+D-1)/D;
	
	tmp=0;
	for(i=0;n[i]!=0 && i<string_length%D;++i)
	{
		tmp*=10;
		tmp+=n[i]-'0';
	}
	--len;
	
	if(i!=0)
	{
		digit[len]=tmp;
		--len;
	}
	
	for(;i<string_length;i+=D)
	{
		tmp=0;
		for(j=0;j<D;++j)
		{
			tmp*=10;
			tmp+=n[i+j]-'0';
		}
	
		digit[len]=tmp;
		--len;
	}
		
	for(pos=length-1;pos>=0 && digit[pos]==0;--pos);
	
	length=pos+1;
}

/************************************************************************************************************************************/
void bigint::print()
{
	int i;
	
	if(length==0)
	{
		putchar('0');
		return;
	}
	printf("%d",digit[length-1]);
	for(i=length-2;i>=0;--i)
		printf("%0*d",D,digit[i]);
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
		result.digit[i]=d%BASE;
		carry=d/BASE;
	}
	for(;i<aaa.length;++i)
	{
		d=aaa.digit[i]+carry;
		result.digit[i]=d%BASE;
		carry=d/BASE;
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
			result.digit[i]=d+BASE;
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
			result.digit[i]=d+BASE;
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
		
		result.digit[i]=tmp%BASE;
		carry=tmp/BASE;
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
		tmp=n*BASE+digit[i];
		if(tmp>=x)
			break;
		n=tmp;
	}
	
	result.length=i+1;
	for(;i>=0;--i)
	{
		n*=BASE;
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
		tmp=n*BASE+digit[i];
		if(tmp>=x)
			break;
		n=tmp;
	}
	
	result.length=i+1;
	for(;i>=0;--i)
	{
		n*=BASE;
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
		result=(result*BASE+digit[i])%x;
	return result;
}

/************************************************************************************************************************************/
long long bigint::operator%(long long x)
{
	long long result=0;
	int i;
	for(i=length-1;i>=0;--i)
		result=(result*BASE+digit[i])%x;
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
bigint::operator int()
{
	int result=0;
	int i;
	for(i=length-1;i>=0;--i)
	{
		result*=BASE;
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
		result*=BASE;
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
		
		//bigint(x).print();
		//printf(" + ");
		//bigint(y).print();
		//printf(" = ");
		
		(bigint(x)*bigint(y)).print();
		puts("");
	}
	return 0;
}
/************************************************************************************************************************************/
