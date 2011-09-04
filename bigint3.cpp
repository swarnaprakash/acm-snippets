#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>

using namespace std;
#define D 200

struct bigint
{
	int digit[D];
	int length;
	static const int BASE=1000;
	static const int MAXD=3; // number of decimal digits in max digit of the BASE. ex 999 for BASE 1000
	
	bigint();
	bigint(int);
	bigint(long long);
	bigint(char *);
	bigint(string);
	
	void print();
	
	bigint operator++();
	bigint operator--();
	bigint operator+(bigint);
	bigint operator-(bigint);
	bigint operator*(int);
	bigint operator*(long long);
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


bigint::bigint()
{
	length=0;
}

bigint::bigint(int n)
{
	int pos=0;
	while(n>0)
	{
		digit[pos++]=n%BASE;
		n/=BASE;
	}
	length=pos;
}

bigint::bigint(long long n)
{
	int pos=0;
	while(n!=0)
	{
		digit[pos++]=n%BASE;
		n/=BASE;
	}
	length=pos;
}

bigint::bigint(char *a)
{
	int i,j,tmp,alen,pos;
	alen=strlen(a);
	pos=0;
	for(i=alen-MAXD;i>=0;i-=MAXD)
	{
		for(tmp=0,j=0;j<MAXD;++j)
		{
			tmp*=10;
			tmp+=a[i+j]-'0';
		}
		digit[pos++]=tmp;
	}
	if(alen%MAXD)
	{
		for(tmp=0,j=0;j<alen%MAXD;++j)
		{
			tmp*=10;
			tmp+=a[j]-'0';
		}
		digit[pos++]=tmp;
	}
	length=pos;
}

/************************************************************************************************************************************/
bigint::bigint(string a)
{
	int i,j,tmp,alen,pos;
	alen=a.size();
	pos=0;
	for(i=alen-MAXD;i>=0;i-=MAXD)
	{
		for(tmp=0,j=0;j<MAXD;++j)
		{
			tmp*=10;
			tmp+=a[i+j]-'0';
		}
		digit[pos++]=tmp;
	}
	if(alen%MAXD)
	{
		for(tmp=0,j=0;j<alen%MAXD;++j)
		{
			tmp*=10;
			tmp+=a[j]-'0';
		}
		digit[pos++]=tmp;
	}
	length=pos;
}

void bigint::print()
{
	if(length==0)
	{
		putchar('0');
		return;
	}
	printf("%d",digit[length-1]);
	for(int i=length-2;i>=0;--i)
		printf("%0*d",MAXD,digit[i]);
}

bigint bigint::operator++()
{
	int i;
	for(i=0;i<length && digit[i]==BASE-1;++i)
		digit[i]=0;
	if(i<length)
		++digit[i];
	else
		digit[length++]=1;
	return *this;
}

bigint bigint::operator--()
{
	int i;
	for(i=0;digit[i]==0;++i)
		digit[i]=BASE-1;
	--digit[i];
	return *this;
}

bigint bigint::operator+(bigint x)
{
	int i,carry,maxlength,d;
	bigint result;
	
	maxlength=length>x.length?length:x.length;		
	carry=0;
	for(i=0;i<maxlength;++i)
	{
		d=(i<length?digit[i]:0)+(i<x.length?x.digit[i]:0)+carry;
		if(d<BASE)
			result.digit[i]=d,carry=0;
		else
			result.digit[i]=d-BASE,carry=1;
	}
	if(carry)
		result.digit[i++]=1;
	result.length=i;
	return result;
}

bigint bigint::operator-(bigint x)
{
	int i,d,borrow;
	bigint result;
	
	borrow=0;
	for(i=0;i<length;++i)
	{
		d=digit[i]-(i<x.length?x.digit[i]:0)-borrow;
		if(d<0)
			result.digit[i]=d+BASE,borrow=1;
		else
			result.digit[i]=d,borrow=0;
	}	
	for(i=length-1;i>=0 && result.digit[i]==0;--i)
		;
	result.length=i+1;
	return result;
}

// (BASE-1)*x<=MAX_INT
bigint bigint::operator*(int x)
{
	int i,carry,d;
	bigint result;
	
	carry=0;
	for(i=0;i<length;++i)
	{
		d=digit[i]*x+carry;
		result.digit[i]=d%BASE;
		carry=d/BASE;
	}
	while(carry>0)
	{
		result.digit[i++]=carry%BASE;
		carry/=BASE;
	}
	result.length=i;
	return result;
}

//(BASE-1)*x<=MAX_LONG_LONG
bigint bigint::operator*(long long x)
{
	int i;
	long long d,carry;
	bigint result;
	
	carry=0;
	for(i=0;i<length;++i)
	{
		d=digit[i]*x+carry;
		result.digit[i]=d%BASE;
		carry=d/BASE;
	}
	while(carry>0)
	{
		result.digit[i++]=carry%BASE;
		carry/=BASE;
	}
	result.length=i;
	return result;
}

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
	for(i=result.length-1;i>=0 && result.digit[i]==0;--i)
		;

	result.length=i+1;
	return result;
}


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


int bigint::operator%(int x)
{
	int result=0;
	int i;
	for(i=length-1;i>=0;--i)
		result=(result*BASE+digit[i])%x;
	return result;
}


long long bigint::operator%(long long x)
{
	long long result=0;
	int i;
	for(i=length-1;i>=0;--i)
		result=(result*BASE+digit[i])%x;
	return result;
}


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

bigint::operator string()
{
	char buf[D];
	int i,len;
	len=sprintf(buf,"%d",digit[length-1]);
	for(i=length-2;i>=0;--i)
		len+=sprintf(buf+len,"%0*d",MAXD,digit[i]);
	return string(buf);
}




int main ()
{
	char x[1000];
	long long y;
	while(cin>>x>>y)
	{
		bigint a(x);
		bigint b(y);
		//(bigint(x)+bigint(y)).print();puts("");
		//bigint(x).print();puts("");
		//bigint(y).print();puts("");
		
		//if(a>=bigint(1))
		//	(--a).print();puts("");
		//if(b>=bigint(1))
		//	(--b).print();puts("");
		//(a*b).print();puts("");
		
		//cout<<(a==b)<<(a!=b)<<(a<=b)<<(a>b)<<(a>=b)<<(a<b)<<"\n";
		
		b.print();puts("");
		(a*y).print();puts("");
		(a/y).print();puts("");
		cout<<(a%y)<<"\n";
		cout<<(long long)b<<"\n";
		
	}
	return 0;
}

