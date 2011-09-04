#define M 100

int s[M];
int rank[M];

void createset(int);
void setunion(int,int);
int findset(int);

void createset(int x)
{
	s[x]=x;
	rank[x]=0;
}

void setunion(int x,int y)
{
	int px,py;
	px=findset(x);
	py=findset(y);

	if(rank[px]>rank[py])
		s[py]=px;
	else
		s[px]=py;
	if(rank[px]==rank[py])
		rank[py]++;
}
int findset(int x)
{
	if(x!=s[x])
		return s[x]=findset(s[x]);
	return x;
}

