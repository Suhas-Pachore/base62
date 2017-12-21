#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buildLookups(int *base62itoa, int *base62atoi);
void base62NextNum(char *prev, char *next, int *base62itoa, int *base62atoi);
void base62NextNum_legacySupport(char *prev, char *next, int *base62itoa, int *base62atoi);

int main(int argc, char *argv[])
{
	char prevnum[3], nextnum[3];

	printf("Hello base62!!\n");
	int base62itoa[62];/*because we have 62 chars*/
	int base62atoi[123];/*for reverve lookup using ascii table*/

	buildLookups(base62itoa, base62atoi);

	strcpy(prevnum,"00");
	prevnum[2]='\0';
	nextnum[2]='\0';
	while(1)
	{
		printf("%s ",prevnum);
		if(prevnum[0] == 'Z' && prevnum[1] == 'Z')
		{
			break;
		}
		else
		{
			base62NextNum_legacySupport(prevnum, nextnum, base62itoa, base62atoi);
		}

		if(nextnum[1] == '0')
		{
			printf("\n\n");
		}
		strcpy(prevnum, nextnum);
	}

	if(argc > 1)
	{
		strncpy(prevnum, argv[1], 2 );
		base62NextNum_legacySupport(prevnum, nextnum, base62itoa, base62atoi);
		printf("\n\n[%s + 1 = %s]\n\n", prevnum, nextnum);
	}

}

void base62NextNum_legacySupport(char *prev, char *next, int *base62itoa, int *base62atoi)
{
	int u = base62atoi[prev[1]]; /*get the value of unit place*/
	int t = base62atoi[prev[0]]; /*get the value of tenth place*/

	/* 00-99 are in base10
	a0-ZZ are in base62 */
	if(t<=9)
	{
		if(u==9)
		{
			/* 00-99 are in base10
			a0-ZZ are in base62 */
			next[1] = base62itoa[0];
			next[0] = base62itoa[t+1];
		}
		else
		{
			next[1] = base62itoa[u+1];
			next[0] = base62itoa[t];
		}
	}
	else
	{
		base62NextNum(prev, next, base62itoa, base62atoi);
	}
	
}

void base62NextNum(char *prev, char *next, int *base62itoa, int *base62atoi)
{
	int u = base62atoi[prev[1]]; /*get the value of unit place*/
	int t = base62atoi[prev[0]]; /*get the value of tenth place*/
	if(u==61)
	{
		if(t==61)
		{
			printf("Exceeded Number Limit\n");
			exit(1);
		}	
		else if(t<61)
		{
			next[1] = base62itoa[0];
			next[0] = base62itoa[t+1];			
		}
	}
	else if(u<61)
	{
		next[1] = base62itoa[u+1];
		next[0] = base62itoa[t];	
	}
}

void buildLookups(int *base62itoa, int *base62atoi)
{
	int i, ascii;

	/*first 0 to 9*/
	for(i=0, ascii='0'; i<10; i++, ascii++)
	{
		base62itoa[i]=ascii;
		base62atoi[ascii]=i;
	}
	/*then a to z*/
	for(i=10, ascii='a'; i<36; i++, ascii++)
	{
		base62itoa[i]=ascii;
		base62atoi[ascii]=i;
	}
	/*last A to Z*/
	for(i=36, ascii='A'; i<62; i++, ascii++)
	{
		base62itoa[i]=ascii;
		base62atoi[ascii]=i;
	}
}
