#include<stdio.h>
#include<string.h>

#define M 1000

main()
{
FILE *f1,*f2;
char a[20],b[20],word1[M],word2[M];
int ok;

puts("\n\t\tWelcome to SWOJ - SWarnaprakash Offline Judge\n\n");

puts("-> compares two files");
puts("-> any non-zero number of consecutive whitespaces is treated as a single whitespace");

puts("\n");

printf("Enter filename_1 -->  ");
scanf("%s",a);

printf("Enter filename_2 -->  ");
scanf("%s",b);

puts("");

f1=fopen(a,"r");
f2=fopen(b,"r");

if(f1==NULL || f2==NULL)
 puts("FILE NOT FOUND");
else
{

ok=1;

while(fscanf(f1,"%s",word1)!=EOF)
{
 if(fscanf(f2,"%s",word2)==EOF)
 {
 ok=0;
 break;
 }
 if(strcmp(word1,word2)!=0)
 {
 ok=0;
 break;
 }
}
if(ok)
 if(fscanf(f2,"%s",word2)!=EOF)
  ok=0;

if(ok)
 puts("ACCEPTED");
else
 puts("WRONG ANSWER");



fclose(f1);
fclose(f2);
}

return 0;
}
