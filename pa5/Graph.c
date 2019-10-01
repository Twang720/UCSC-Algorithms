/*
 * Timothy Wang
 * tqwang
 * CS101 Tantalo
 * Graph.c
 *
 * Creates a Graph ADT and its related functions, including a GraphObj structure.
 */
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct GraphObj
{
	List* adj;
	char* color;
	int* parent;
	int* discover;
	int* finish;
	int vertices;
	int edges;
} GraphObj;

#include "Graph.h"

/*** Constructors-Destructors ***/
Graph newGraph(int n)
{
	Graph G = malloc(sizeof(GraphObj));
	G->adj = malloc(sizeof(List)*(n+1));
	for(int i = 1; i<=n; i++)
	{
		G->adj[i] = newList();
	}
	G->color = malloc(sizeof(char)*(n+1));
	for(int i = 1; i<=n; i++)
	{
		G->color[i] = 'w';
	}
	G->parent = malloc(sizeof(int)*(n+1));
	for(int i = 1; i <=n; i++)
	{
		G->parent[i] = NIL;
	}
	G->discover = malloc(sizeof(int)*(n+1));
	for(int i = 1; i<=n; i++)
	{
		G->discover[i] = UNDEF;
	}
	G->finish = malloc(sizeof(int)*(n+1));
	for(int i = 1; i<=n; i++)
	{
		G->finish[i] = UNDEF;
	}
	G->vertices = n;
	G->edges = NIL;
	return G;
}
void freeGraph(Graph* pG)
{
	if(pG!=NULL && *pG!=NULL)
	{
		for(int i = 1; i <= getOrder(*pG); i++) {
			freeList(&((*pG)->adj[i]));
			free((*pG)->adj[i]);
		}
		free((*pG)->adj);
		(*pG)->adj = NULL;
		free((*pG)->parent);
		(*pG)->parent = NULL;
		free((*pG)->discover);
		(*pG)->discover = NULL;
		free((*pG)->finish);
		(*pG)->finish = NULL;
		free((*pG)->color);
		(*pG)->color = NULL;
		free(*pG);
		*pG = NULL;
	}
}
/*** Access functions ***/
int getOrder(Graph G)
{
	return G->vertices;
}
int getSize(Graph G)
{
	return G->edges;
}
int getParent(Graph G, int u)
{
	return G->parent[u];
}
int getDiscover(Graph G, int u)
{
	return G->discover[u];
}
int getFinish(Graph G, int u)
{
	return G->finish[u];
}
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v)
{
	List P = G->adj[u];
	List Q = G->adj[v];
	if(isEmpty(P))
	{
		append(P, v);
	}
	else
	{
		moveFront(P);
		while(get(P)!=-2)
		{
			if(get(P) == v)
			{
				break;
			}
			if(get(P) > v)
			{
				insertBefore(P, v);
				break;
			}
			moveNext(P);
		}
		if(back(P) < v)
		{
			append(P, v);
		}
	}
	if(isEmpty(Q))
	{
		append(Q, u);
	}
	else
	{
		moveFront(Q);
		while(get(Q) != -2)
		{
			if(get(Q) == u)
			{
				break;
			}
			if(get(Q) > u)
			{
				insertBefore(Q, u);
				break;
			}
			moveNext(Q);
		}
		if(back(Q) < u)
		{
			append(Q, u);
		}
	}
	G->edges++;
}
void addArc(Graph G, int u, int v)
{
	List P = G->adj[u];
	if(isEmpty(P))
	{
		append(P, v);
	}
	else
	{
		moveFront(P);
		while(get(P) != -2)
		{
			if(get(P) == v)
			{
				break;
			}
			if(get(P) > v)
			{
				insertBefore(P, v);
				break;
			}
			moveNext(P);
		}
		if(back(P) < v)
		{
			append(P, v);
		}
	}
	G->edges++;
}
void Visit(Graph G, int x, int* time)
{
	G->discover[x] = ++(*time);
	G->color[x] = 'g';
	List P = G->adj[x];
	moveFront(P);
	while(get(P) != -2)
	{
		int y = get(P);
		if(G->color[y] == 'w')
		{
			G->parent[y] = x;
			Visit(G, y, time);
		}
		moveNext(P);
	}
	G->color[x] = 'b';
	G->finish[x] = ++(*time);
}
void DFS(Graph G, List S)
{
	if(length(S) != getOrder(G))
	{
		fprintf(stderr, "Length of list is not n\n");
		return;
	}
	moveFront(S);
	for(int i = 1; i<= getOrder(G); i++)
	{
		G->color[i] = 'w';
		G->parent[i] = NIL;
	}
	int time = 0;
	int count = 0;
	while(front(S) != -2)
	{
		if(G->color[front(S)] == 'w')
		{
			count++;
			Visit(G, front(S), &time);
		}
		deleteFront(S);
	}
	for(int i = 1; i<=getOrder(G); i++)
	{
		moveFront(S);
		while(get(S)!=-2)
		{
			if(G->finish[get(S)] < G->finish[i])
			{
				insertBefore(S, i);
				break;
			}
			moveNext(S);
		}
		if(get(S)==-2)
		{
			append(S, i);
		}
	}
}
/*** Other operations ***/
Graph transpose(Graph G)
{
	Graph N = newGraph(getOrder(G));
	for(int i = 1; i<=getOrder(N); i++)
	{
		List P = G->adj[i];
		moveFront(P);
		while(get(P) != -2)
		{
			int j = get(P);
			addArc(N, j, i);
			moveNext(P);
		}
	}
	return N;
}
Graph copyGraph(Graph G)
{
	Graph N = newGraph(getOrder(G));
	for(int i = 1; i<=getOrder(N); i++)
	{
		List P = G->adj[i];
		moveFront(P);
		while(get(P) != -2)
		{
			int j = get(P);
			addArc(N, i, j);
			moveNext(P);
		}
	}
	return N;
}
void printGraph(FILE* out, Graph G)
{
	for(int i = 1; i<=getOrder(G); i++)
	{
		fprintf(out, "%d: ", i);
		List P = G->adj[i];
		moveFront(P);
		while(get(P)!=-2)
		{
			fprintf(out, "%d ", get(P));
			moveNext(P);
		}
		fprintf(out, "\n");
	}
}
