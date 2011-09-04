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
