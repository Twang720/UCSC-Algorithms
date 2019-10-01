//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[])
{
	
	int i=0, n=0, count=0;
   	FILE *in, *in2, *out;
   	char line[MAX_LEN];

   	// check command line for correct number of arguments
   	if( argc != 3 )
	{
      		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}

   	// open files for reading and writing 
   	in = fopen(argv[1], "r");
	in2 = fopen(argv[1], "r");
   	out = fopen(argv[2], "w");
   	if( in==NULL )
	{
      		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	}
   	if( out==NULL )
	{
      		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   	}

   	/* read each line of input file, then count and print tokens */
   	while( fgets(line, MAX_LEN, in) != NULL)  
	{
      		count++;
   	}

	// declare array and put in lines from input file
	char** arr = calloc(count, sizeof(char*));
	while( fgets(line, MAX_LEN, in2) != NULL)
	{
		char* copy = malloc(strlen(line)+1);
		strcpy(copy, line);
		arr[i++] = copy;
	}

	// Create list of indices sorted lexographically
	List L = newList();
	append(L, n);
	n++;
	while( n<i )
	{
		moveFront(L);
		while(index(L)>=0)
		{
			int x = strcmp(arr[n], arr[get(L)]);
			if( x<0 )
			{
				insertBefore(L, n);
				n++;
				break;
			}
			moveNext(L);
		}
		if(index(L)==-1)
		{
			append(L, n);
			n++;
		}
	}
	
	// Print array in list order
	moveFront(L);
	while(index(L)>=0)
	{
		fprintf(out, "%s", arr[get(L)]);
		moveNext(L);
	}

	// Free memory
	freeList(&L);
	for(int j = 0; j<i; j++)
	{
		free(arr[j]);
	}
	free(arr);


   	/* close files */
   	fclose(in);
   	fclose(out);
	fclose(in2);

   	return(0);
}
