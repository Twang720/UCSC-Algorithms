/*
 * Timmy Wang
 * CMPS101
 * List.h
 */
#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
        int data;
        struct NodeObj* next;
        struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;
 
// private ListObj type
typedef struct ListObj
{
        Node front;
        Node back;
        Node cursor;
        int index;
        int length;
} ListObj;
 
// private List type
typedef ListObj* List;
 

// Constructors-Destructors ---------------------------------------------------
Node newNode(int data);
void freeNode(Node *pN);
List newList();
void freeList(List* pL);
// Access functions -----------------------------------------------------------
int isEmpty(List L);
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);
// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);

#endif
