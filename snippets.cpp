void tolow(string &x)
{
	int i;
	for(i=0;i<x.length();++i)
		if(x[i]>='A' && x[i]<='Z')
			x[i]+=32;
}

/************************************************************************************************************************************/
void tohigh(string &x)
{
	int i;
	for(i=0;i<x.length();++i)
		if(x[i]>='a' && x[i]<='z')
			x[i]-=32;
}

/************************************************************************************************************************************/
vector<int> getvint(string s)
{
	int d;
	vector<int> ans;
	stringstream ss;
	
	ss<<s;
	while(ss>>d)
		ans.PB(d);
	return ans;
}

/************************************************************************************************************************************/
vector<string> getvstring(string s)
{
	string d;
	vector<string> ans;
	stringstream ss;
	
	ss<<s;
	while(ss>>d)
		ans.PB(d);
	return ans;
}

/************************************************************************************************************************************/
template<class T>
string tostring(T &x)
{
	stringstream ss;
	ss<<x;
	return ss.str();
}

/************************************************************************************************************************************/
bool isprefix(string a,string b)
{
	if(a.size()>b.size())
		return false;
		
	if(b.substr(0,a.size())==a)
		return true;
	else
		return false;
}

/************************************************************************************************************************************/
bool issuffix(string a,string b)
{
	if(a.size()>b.size())
		return false;
	
	if(b.substr((b.size()-a.size()))==a)
		return true;
	else
		return false;
}

/************************************************************************************************************************************/
vector<string> tokenize(string s,string delimiters)
{
	char ns[s.size()+1];
	char delim[delimiters.size()+1];
	char *token;
	
	strcpy(ns,s.c_str());
	strcpy(delim,delimiters.c_str());
	
	token=strtok(ns,delim);
	
	vector<string> ans;
	
	while(token!=NULL)
	{
		ans.push_back( (string) token);
		token=strtok(NULL,delim);
	}
	return ans;
}

/************************************************************************************************************************************/
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

/************************************************************************************************************************************/
template<class T>
T lcm(T m,T n)
{
	return m/gcd(m,n)*n;
}

/************************************************************************************************************************************/
int fact(int n)
{
	int i,ans=1;
	for(i=1;i<=n;++i)
		ans*=i;
	return ans;
}

/************************************************************************************************************************************/
bool isprime(int n)
{
	int i,sq;
	
	if(n<2)
		return false;
	if(n==2)
		return true;
	if(n%2==0)
		return false;

	sq=(int)(sqrt((double)n)+1);

	for(i=3;i<=sq;i+=2)
		if(n%i==0)
			return false;
	return true;
}

/************************************************************************************************************************************/
void binomial()
{
	int i,j;
	
	bino[0][0]=bino[1][0]=bino[1][1]=1;
	for(i=2;i<=34;++i)
	{
		bino[i][0]=bino[i][i]=1;
		for(j=1;j<i;++j)
			bino[i][j]=bino[i-1][j]+bino[i-1][j-1];
	}
}

/************************************************************************************************************************************/
void sieve(int n)
{
	int i,j,sq;
	
	sq=(int)(sqrt( (double) n)+1);
	prime[0]=prime[1]=false;
	prime[2]=true;
	
	for(i=3;i<n;++i)
		prime[i]=(i&1);
		
	for(i=3;i<=sq;i+=2)
		if(prime[i])
			for(j=i*i;j<n;j+=i)
				prime[j]=false;
}

/************************************************************************************************************************************/
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

/************************************************************************************************************************************/
int modulo(int a,int b,int c)
{
	LL x=1,y=a;
	
	while(b>0)
	{
		if(b&1)
			x=(x*y)%c;
		y=(y*y)%c;
		b>>=1;
	}
	return (x%c);
}

/************************************************************************************************************************************/
bool isvowel(char c)
{
	c=tolower(c);
	return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');
}

/************************************************************************************************************************************/
bool isleap(int y)
{
	if(y%4!=0)
		return false;
	if(y%100==0 && y%400!=0)
		return false;
	return true;
}

/************************************************************************************************************************************/
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};

int dx[]={1,1,-1,-1};
int dy[]={1,-1,-1,1};

int dx[]={1,-1,0,0,1,1,-1,-1};
int dy[]={0,0,1,-1,1,-1,-1,1};

/************************************************************************************************************************************/
int triarea(int xx1,int yy1,int xx2,int yy2,int xx3,int yy3)
{
	// returns twice the area ;
	int Vx1,Vx2,Vy1,Vy2,area;
	
	Vx1=xx3-xx1;
	Vy1=yy3-yy1;
	Vx2=xx2-xx1;
	Vy2=yy2-yy1;
	
	area=Vx1*Vy2-Vy1*Vx2;
	return abs(area);
}
