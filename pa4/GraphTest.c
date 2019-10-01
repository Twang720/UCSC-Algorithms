/*
 * Timothy Wang
 * tqwang
 * CS101 Tantalo
 * GraphTest.c
 *
 * Tests the Graph ADT for bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main()
{
	// Test making new graph
	Graph G = newGraph(2);
	printf("%d\n", getOrder(G));
	printf("%d\n", getSize(G));
	printf("%d\n", getSource(G));
	printf("%d\n", getParent(G,1));
	printf("%d\n", getDist(G,1));

	addEdge(G, 1, 2);
	printf("%d\n", getSize(G));

	freeGraph(&G);

	Graph A = newGraph(100);

	addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        BFS(A, 64);
	printf("%d\n", getDist(A, 2));

	BFS(A,4);
	printf("%d\n", getDist(A, 42));

	BFS(A, 42);
	printf("%d\n", getParent(A, 2));
	makeNull(A);

	addEdge(A, 64, 4);
        addEdge(A, 64, 3);
        addEdge(A, 42, 2);
        addEdge(A, 2, 64);
        addEdge(A, 4, 2);
        addEdge(A, 3, 42);
        BFS(A, 42);
	printf("%d\n", getParent(A, 64));
	
	printGraph(stdout, A);
	freeGraph(&A);
}
