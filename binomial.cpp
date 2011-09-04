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
