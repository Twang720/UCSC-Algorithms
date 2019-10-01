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
		addEdge(G, x, y);
      	}
	
	printGraph(out, G);
	fprintf(out, "\n");

	while( fgets(line, MAX_LEN, in) != NULL )
	{
		token = strtok(line, " \n");
		int x = atoi(token);
		token = strtok(NULL, " \n");
		int y = atoi(token);
		if(x==0 && y==0)
			break;
		BFS(G, x);
		if(getDist(G,y) != -1)
		{
			fprintf(out, "The distance from %d to %d is %d\n", x,  y, getDist(G, y));
			List L = newList();
			getPath(L, G, y);
			fprintf(out, "A shortest %d-%d path is: ", x, y);
			printList(out, L);
			fprintf(out, "\n\n");
		}
		else
		{
			fprintf(out, "The distance from %d to %d is infinity\n", x, y);
			fprintf(out, "No %d-%d path exists\n", x, y);
		}
	}

	freeGraph(&G);

   	/* close files */
   	fclose(in);
   	fclose(out);

   	return(0);
}	
