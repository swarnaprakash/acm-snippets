/********************************************************************************************************************************

						Knuth-Morris-Pratt string matching
							written by U.Swarnaprakash
						
						http://www.ics.uci.edu/~eppstein/161/960227.html
						
************************************************************************************************************************************/


#include<cstdio>
#include<iostream>
#include<string>

using namespace std;

void kmp(string,string);

int main()
{
	string pattern,text;
	
	cin>>pattern>>text;
	kmp(pattern,text);
}

void kmp(string pattern,string text)
{
	int overlap[pattern.size()+1];
	
	//compute overlap
	int i;
	overlap[0]=-1;
	/*
													  (assuming 0-based index)
		consider overlap(x-1).If current character == pattern(length(overlap(x-1))) then we can append this
		character to obtain overlap(x).Thus overlap(x)=overlap(x-1)+1 initially and if the previously 
		mentioned characters are equal while loop condition is false.
		Now if the characters are not equal...
		assume overlap(x-1) begins at some postion p.There is no point in looking for beginning of overlap(x)
		before p since if there is a overlap that begins before p then that will the beginning of overlap(x-1).
		So we need to analyse the suffixes that end in x and start after p.Now consider the substring that starts 
		at p and ends at x-1.Since this is a overlap this is prefix of pattern.We need to try the longest possible
		suffix of this substring ,which is a prefix of the pattern.
		overlap[i+1]=overlap[overlap[i+1]-1]+1; does this.
	
	*/
	
	for(i=0;i<pattern.size();++i)
	{
		overlap[i+1]=overlap[i]+1;
		while(overlap[i+1]>0 && pattern[i]!=pattern[overlap[i+1]-1])
			overlap[i+1]=overlap[overlap[i+1]-1]+1;
	}
	
	for(i=0;i<=pattern.size();++i)
		cout<<overlap[i]<<endl;
	
	int start,j;
	i=0;start=0;
	
	overlap[0]=0; // don't forget this or you will access text[-1]
	
	// for this part see the link given above
	while(i<text.size())
	{
		for(j=start;i+j<text.size() && j<pattern.size() && pattern[j]==text[i+j];++j);
		
		if(j==pattern.size())
			cout<<"pattern found at "<<i<<endl;
			
		//cout<<"j="<<j<<endl;
		assert(j<=pattern.size());	
		i=i+max(1,j-overlap[j]);
		start=overlap[j];
	} 
}

