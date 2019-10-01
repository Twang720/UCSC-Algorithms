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
	int* distance;
	int* parent;
	int vertices;
	int edges;
	int source;
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
	G->distance = malloc(sizeof(int)*(n+1));
	for(int i = 1; i <=n; i++)
	{
		G->distance[i] = INF;
	}
	G->vertices = n;
	G->edges = NIL;
	G->source = NIL;
	return G;
}
void freeGraph(Graph* pG)
{
	if(pG!=NULL && *pG!=NULL)
	{
		free((*pG)->adj);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
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
int getSource(Graph G)
{
	return G->source;
}
int getParent(Graph G, int u)
{
	return G->parent[u];
}
int getDist(Graph G, int u)
{
	return G->distance[u];
}
void getPath(List L, Graph G, int u)
{
	int s = G->source;
	if(s == NIL)
	{
		return;
	}
	if(getDist(G, u) == INF)
	{
		append(L, NIL);
		return;
	}
	List P = newList();
	while(u != NIL)
	{
		append(P, u);
		u = G->parent[u];
	}
	moveBack(P);
	while(get(P) != -2)
	{
		append(L, get(P));
		deleteBack(P);
		moveBack(P);
	}		
}
/*** Manipulation procedures ***/
void makeNull(Graph G)
{	
	for(int i = 1; i<=getOrder(G); i++)
	{
		List L = G->adj[i];
		clear(L);
	}
	G->edges = 0;
}
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
void BFS(Graph G, int s)
{
	for(int i = 1; i<= getOrder(G); i++)
	{
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = 'g';
	G->distance[s] = 0;
	List L = newList();
	append(L, s);
	while(front(L)!=-2)
	{
		int x = front(L);
		deleteFront(L);
		List P = G->adj[x];
		moveFront(P);
		while(get(P)!=-2)
		{
			int y = get(P);
			if(G->color[y] == 'w')
			{
				G->color[y] = 'g';
				G->distance[y] = G->distance[x]+1;
				G->parent[y] = x;
				append(L, y);
			}
			moveNext(P);
		}
		G->color[x] = 'b';
	}
	G->source = s;
}
/*** Other operations ***/
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
