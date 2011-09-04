#include<cstring>
#include<string>
#include<vector>
#include<cstdio>
#include<iostream>

using namespace std;


vector<string> tokenize(string,string);

int main()
{
	string s="words separated by spaces -- and, punctuation!";
	vector<string> a;
	a=tokenize(s," .,;:!-");
	int i;
	for(i=0;i<a.size();++i)
		cout<<a[i]<<endl;
	return 0;
}

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
