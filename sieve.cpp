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
