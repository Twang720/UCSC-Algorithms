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
	printf("%d\n", getParent(G,1));

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
	List S = newList();
	append(S, 2);
	append(S, 3);
	append(S, 4);
	append(S, 42);
	append(S, 64);
        DFS(A, S);
	printf("%d\n", getDiscover(A, 2));
	printf("%d\n", getFinish(A, 2));

	Graph B = transpose(A);

	DFS(A,S);

	printGraph(stdout, A);
	printGraph(stdout, B);
	freeGraph(&A);
	freeGraph(&B);
}
