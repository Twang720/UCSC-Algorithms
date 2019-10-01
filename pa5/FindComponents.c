//-----------------------------------------------------------------------------
// Timothy Wang
// tqwang
// CS101 Tantalo
// FindPath.c
//
// Takes in two files, input and output, and spits out the adjacency list of
// the given graph vertices and edges, as well as a shortest path from certain
// sources to destinations.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 160

int main(int argc, char * argv[])
{
   	int n = 0;
   	FILE *in, *out;
   	char line[MAX_LEN];
	char* token;

   	// check command line for correct number of arguments
   	if( argc != 3 )
	{
   		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}

   	// open files for reading and writing 
   	in = fopen(argv[1], "r");
   	out = fopen(argv[2], "w");
   	if( in==NULL )
	{
   	   	printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	}
   	if( out==NULL )
	{
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   	}

   	/* read each line of input file, then count and print tokens */
	fgets(line, MAX_LEN, in);
	n = atoi(line);
	Graph G = newGraph(n);

   	while( fgets(line, MAX_LEN, in) != NULL )  
	{
		token = strtok(line, " \n");
		int x = atoi(token);
		token = strtok(NULL, " \n");
		int y = atoi(token);
		if(x==0 && y==0)
			break;
		addArc(G, x, y);
      	}
	
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");

	List S = newList();
	for(int i = 1; i<=getOrder(G); i++)
	{
		append(S, i);
	}
	DFS(G, S);
	Graph T = transpose(G);
	DFS(T, S);

	int count = 0;
	List L = newList();
	moveFront(S);
	while(get(S)!=-2)
	{
		if(getParent(T, get(S)) == NIL)
		{
			count++;
			prepend(L, get(S));
			moveNext(S);
			moveFront(L);
			while(get(S)!=-2 && getParent(T,get(S)) != NIL)
			{
				insertAfter(L, get(S));
				moveNext(L);
				moveNext(S);
			}
		}
		else
			moveNext(S);
	}

	fprintf(out, "G contains %d strongly connected components: \n", count);
	moveFront(L);
	for(int i = 1; i<=count; i++)
	{
		if(getParent(T, get(L)) == NIL)
		{
			fprintf(out, "Component %d: %d", i, get(L));
			moveNext(L);
			while(get(L)!=-2 && getParent(T, get(L)) != NIL)
			{
				fprintf(out, " %d", get(L));
				moveNext(L);
			}
			fprintf(out, "\n");
		}
		else
			moveNext(L);
	}

	freeGraph(&G);
	freeList(&L);

   	/* close files */
   	fclose(in);
   	fclose(out);

   	return(0);
}	
