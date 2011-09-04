#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>

#define M 65536
#define LGM 17

using namespace std;


struct suffix
{
	int a;
	int b;
	int p;
	
	bool operator<(const suffix &x) const
	{
		if(a!=x.a)	
			return a<x.a;
		return b<x.b;
	}
	
	bool operator==(const suffix &x) const
	{
		return a==x.a && b==x.b;
	}
};

char a[M];
suffix s[M];
int sa[LGM][M];
int spos;

bool compare(int x,int y)
{
	return strcmp(a+x,a+y)<0;
}


vector<int> fast()
{
	int len=strlen(a);
	for(int i=0;i<len;++i)
		sa[0][i]=a[i]-'a';
	
	int i,stp;
	for(i=stp=1;;++i,stp<<=1)
	{
		for(int j=0;j<len;++j)
			s[j]=(suffix){sa[i-1][j],(j+stp<len?sa[i-1][j+stp]:-1),j};
		sort(s,s+len);
		
		sa[i][s[0].p]=0;
		for(int j=1;j<len;++j)
			if(s[j]==s[j-1])
				sa[i][s[j].p]=sa[i][s[j-1].p];
			else
				sa[i][s[j].p]=j;
				
		if(stp>=len)
			break;
	}
	
	vector<int> v(len);
	for(int j=0;j<len;++j)
		v[sa[i][j]]=j;
	return v;
}

vector<int> slow()
{
	int len=strlen(a);
	vector<int> v(len);
	for(int i=0;i<len;++i)
		v[i]=i;
	sort(v.begin(),v.end(),compare);
	return v;
}

void display(vector<int> v)
{
	for(int i=0;i<v.size();++i)
		printf("%d ",v[i]);
	puts("");
}

int main ()
{
	
	//scanf("%s",a);
	
	int cnt=0;
	
	for(char i='a';i<='e';++i)
		for(char j='a';j<='e';++j)
			for(char k='a';k<='e';++k)
				for(char l='a';l<='e';++l)
					for(char m='a';m<='e';++m)
						for(char n='a';n<='e';++n)
							for(char o='a';o<='e';++o)
								for(char p='a';p<='e';++p)
						{
							++cnt;
							if(cnt%1000==0)
								printf("%d\n",cnt);
							a[0]=i,a[1]=j,a[2]=k,a[3]=l,a[4]=m,a[5]=n,a[6]=o,a[7]=p,a[8]=0;
							assert(fast()==slow());
						}
	return 0;
}

