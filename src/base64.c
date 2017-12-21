#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buildLookups(int *base64itoa, int *base64atoi);
void base64NextNum(char *prev, char *next, int *base64itoa, int *base64atoi);

int main(int argc, char *argv[])
{
	char prevnum[3], nextnum[3];
	int base64itoa[64];/*because we have 64 chars*/
	int base64atoi[128];/*for reverse lookup using ascii table*/

	buildLookups(base64itoa, base64atoi);

	if(argc > 1 && strlen(argv[1])==2)
	{
		strncpy(prevnum, argv[1], 2 );
		base64NextNum(prevnum, nextnum, base64itoa, base64atoi);
		printf("[%s + 1 = %s]\n", prevnum, nextnum);
	}
	else
	{
		printf("ERR/Invalid Arguments.\n[usage: a.out a1]\n");
	}
}

void base64NextNum(char *prev, char *next, int *base64itoa, int *base64atoi)
{
	int prev_num =  ((base64atoi[prev[0]] << 6) + (base64atoi[prev[1]]));
	// prev_num = (int val of base64 char at Tenth place, left shifted by 6)+(int val of base64 char at unit place)

	if(prev_num < 640) //number below 640 are 00 to 99 and they are decimal numbers
	{
		prev_num = atoi(prev);
		if(prev_num < 99) //numbers below 99 are base10 and follow simple base10 arithematic
		{
			sprintf(next, "%d", (prev_num + 1));
			return;
		}
		prev_num = 639; //it sets the next number after 99 to a0; skipps intermidiate 540 numbers for simplicity.
	}

	int next_num = prev_num + 1;
	if(next_num >> 12) //number exceeds base64 limit, cannot have more than 12 bits. right-shift 12 bits.
	{
		printf("Exceeded Number Limit\n");
		exit(1);
	}
	next[0] = base64itoa[(next_num >> 6)]; //first 6 bits converted to base64 char. right shift 6 bits to get first 6 bits.
	next[1] = base64itoa[(next_num & 63)]; //mask all higher bits except last 6 bits. 63-->00111111. masking gets last 6 bits.

	// - (starting number base64 encoding at integer 640, so deduct it)
	// + (continuation after 99 decimal system, so make this number as 100)
	printf("[%d + 1 = %d]\n",(prev_num-640+100),(next_num-640+100));
}

void buildLookups(int *base64itoa, int *base64atoi)
{
	int i, ascii;

	/*first 0 to 9*/
	for(i=0, ascii='0'; i<10; i++, ascii++)
	{
		base64itoa[i]=ascii;
		base64atoi[ascii]=i;
	}
	/*then a to z*/
	for(i=10, ascii='a'; i<36; i++, ascii++)
	{
		base64itoa[i]=ascii;
		base64atoi[ascii]=i;
	}
	/*last A to Z*/
	for(i=36, ascii='A'; i<62; i++, ascii++)
	{
		base64itoa[i]=ascii;
		base64atoi[ascii]=i;
	}

	/*finally @ and #*/
	{
		base64itoa[62]='@';
		base64atoi['@']=62;
		base64itoa[63]='#';
		base64atoi['#']=63;
	}
}
