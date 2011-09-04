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


