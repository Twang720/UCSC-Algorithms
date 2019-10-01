/*
 * Timothy Wang
 * tqwang
 * CS101 Tantalo
 * Graph.h
 *
 * Header file defining functions and GraphObj pointer structure
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include "List.h"
#define UNDEF -1
#define NIL 0

struct GraphObj;
typedef struct GraphObj * Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
