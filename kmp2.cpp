/********************************************************************************************************************************

						Knuth-Morris-Pratt string matching
						(stream based input)
							written by U.Swarnaprakash
						
						http://www.ics.uci.edu/~eppstein/161/960227.html
						
************************************************************************************************************************************/
//see kmp1.cpp

#include<cstdio>
#include<iostream>
#include<string>

using namespace std;

void kmp(string);

int main()
{
	string pattern,text;
	
	cin>>pattern;
	char a[10];
	gets(a);
	kmp(pattern);
}

void kmp(string pattern)
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
	overlap[0]=0; // don't forget this or you will access text[-1]
	
	
	int j=0;
	i=0;
	
	char c;
	
	/*
	Let B be beginning of the substring we are in text that we are checking currently.
	At any time B=i-j.when there is a mismatch in kmp1 we increment the beginning by j-overlap(j).
	and the inner loop begins from overlap(j).
	==> B must be incremented by j-overlap(j).
	==> B = B+ j-overlap(j).
	==> B = i+j-j-overlap(j) 
		  = i-overlap(j) 
		So we change j to overlap(j)
		
	*/
	
	while(1)
	{
		++i;
		c=getchar();
		if(c=='\n')
			break;
		while(1)
		{
			if(c==pattern[j])
			{
				++j;
				if(j==pattern.size())
				{
					printf("pattern found at %d\n",i-pattern.size());
					j=overlap[j];
				}
				break;
			}
			else if(j==0)
				break;
			else
				j=overlap[j];
			
		}
	}
	
}

