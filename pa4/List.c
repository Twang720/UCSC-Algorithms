//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include "List.h"

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
   	N->next = NULL;
	N->prev = NULL;
   	return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
   	if( pN!=NULL && *pN!=NULL )
	{
      		free(*pN);
      		*pN = NULL;
   	}
}

// newList()
// Returns reference to new empty List object.
List newList()
{
   	List L;
   	L = malloc(sizeof(ListObj));
   	L->front = L->back = L->cursor = NULL;
   	L->length = 0;
	L->index = -1;
   	return L;
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL)
{
   	if(pL!=NULL && *pL!=NULL) 
	{ 
      		while( !isEmpty(*pL) )
		{ 
			Node N = (*pL)->front;
			freeNode(&N);
         		deleteFront(*pL); 
      		}
      		free(*pL);
      		*pL = NULL;
   	}
}

// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L)
{
   	if( L==NULL )
	{
      		fprintf(stderr, "List Error: calling isEmpty() on NULL List reference\n");
      		exit(1);
   	}
   	return L->length==0;
}

// length()
// Returns the length of L.
int length(List L)
{
   	if( L==NULL )
	{
      		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
      		exit(1);
   	}
   	return L->length;
}

// index()
// Returns the index of cursor in L
int index(List L)
{
	if( L==NULL )
        {
                fprintf(stderr, "List Error: calling index() on NULL List reference\n");
                exit(1);
        }
	return L->index;
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L)
{
   	if( L==NULL )
	{
      		fprintf(stderr,"List Error: calling front() on NULL List reference\n");
      		exit(1);
   	}
   	if( isEmpty(L) )
	{
		return -2;
   	}
   	return L->front->data;
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L)
{
        if( L==NULL )
        {
                fprintf(stderr,"List Error: calling back() on NULL List reference\n");
                exit(1);
        }
        if( isEmpty(L) )
        {
                fprintf(stderr, "List Error: calling back() on an empty List\n");
                exit(1);
        }
        return L->back->data;
}

// get()
// Returns the value of current position in L.
// // Pre: !isEmpty(L)
int get(List L)
{
	if( L==NULL)
	{
		fprintf(stderr,"List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) )
	{
		return -2;
	}
	if( L->cursor==NULL )
	{
		return -2;
	}
	return L->cursor->data;

}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B)
{
   	int eq = 0;
   	Node N = NULL;
   	Node M = NULL;

   	if( A==NULL || B==NULL )
	{
      		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
      		exit(1);
   	}

   	eq = ( A->length == B->length );
   	N = A->front;
   	M = B->front;
   	while( eq && N!=NULL)
	{
      		eq = (N->data==M->data);
      		N = N->next;
      		M = M->next;
   	}
   	return eq;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Clears List L
void clear(List L)
{
	L->front = NULL;
	L->back = NULL;
	L->cursor =  NULL;
	L->length = 0;
	L->index = -1;	
}

// moveFront()
// Moves cursor to front
// Pre: !isEmpty(L)
void moveFront(List L)
{
	if( L==NULL)
	{
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) )
	{
		return;
	}
	L->cursor = L->front;
	L->index = 0;
}

// moveBack()
// Moves cursor to back
// Pre: !isEmpty(L)
void moveBack(List L)
{
	if( L==NULL)
	{
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) )
	{
		return;
	}
	L->cursor = L->back;
	L->index = length(L)-1;
}

// movePrev()
// Moves cursor one space back
// Pre: !isEmpty(L)
void movePrev(List L)
{
	if( L==NULL)
	{
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) )
	{
		return;
	}
	if( L->cursor==NULL )
	{
		fprintf(stderr, "List Error: calling movePrev() with null cursor\n");
		exit(1);
	}
	L->cursor = L->cursor->prev;
	L->index--;
}

// moveNext()
// Moves cursor one space forward
// Pre: !isEmpty(L)
void moveNext(List L)
{
	if( L==NULL)
	{
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) )
	{
		return;
	}
	if( L->cursor==NULL )
	{
		fprintf(stderr, "List Error: calling moveNext() with null cursor\n");
		exit(1);
	}
	L->cursor = L->cursor->next;
	if( L->cursor==NULL )
	{
		L->index = -1;
	}
	else
	{
		L->index++;
	}
}

// prepend()
// Places new data element at the beginning of L
void prepend(List L, int data)
{
   	Node N = newNode(data);

   	if( L==NULL )
	{
      		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      		exit(1);
   	}
   	if( isEmpty(L) ) 
	{ 
      		L->front = L->back = N; 
   	}
	else
	{ 
      		L->front->prev = N; 
		N->next = L->front;
      		L->front = N; 
   	}
	if(index(L)!=-1)
	{
		L->index++;
	}
   	L->length++;
}

// append()
// Places new data element at the end of L
void append(List L, int data)
{
   	Node N = newNode(data);

   	if( L==NULL )
	{
      		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      		exit(1);
   	}
   	if( isEmpty(L) ) 
	{ 
      		L->front = L->back = N; 
   	}
	else
	{ 
      		L->back->next = N; 
		N->prev = L->back;
      		L->back = N; 
   	}
   	L->length++;
}

// insertBefore()
// Inserts element before cursor
// Pre: L->cursor != NULL
void insertBefore(List L, int data)
{
	Node N = newNode(data);
	if( L==NULL )
	{
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if( L->cursor==NULL )
	{
		fprintf(stderr, "List Error: calling insertBefore with NULL cursor\n");
		exit(1);
	}
	if( L->cursor!=L->front )
	{
		((L->cursor)->prev)->next = N;
	}
	else
	{
		L->front = N;
	}
	N->prev = (L->cursor)->prev;
	N->next = L->cursor;
	(L->cursor)->prev = N;
	L->index++;
	L->length++;
}

// insertAfter()
// Inserts element after cursor
// Pre: L->cursor != NULL
void insertAfter(List L, int data)
{
	Node N = newNode(data);
	if( L==NULL )
	{
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	if( L->cursor==NULL )
	{
		fprintf(stderr, "List Error: calling insertAfter with NULL cursor\n");
		exit(1);
	}
	if( L->cursor!=L->back )
	{
		((L->cursor)->next)->prev = N;
	}
	else
	{
		L->back = N;
	}
	N->next = (L->cursor)->next;
	N->prev = L->cursor;
	(L->cursor)->next = N;
	L->length++;
}

// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L)
{
   	Node N = NULL;

   	if( L==NULL )
	{
      		fprintf(stderr, "Queue Error: calling deleteFront() on NULL List reference\n");
      		exit(1);
   	}
   	if( isEmpty(L) )
	{
      		fprintf(stderr, "List Error: calling deleteFront on an empty List\n");
      		exit(1);
   	}
   	N = L->front;
	if( L->cursor == L->front )
	{
		L->cursor = NULL;
	}
   	if( length(L)>1 ) 
	{ 
      		L->front = L->front->next; 
   	}
	else
	{ 
      		L->front = L->back = NULL; 
   	}
	L->index--;
   	L->length--;
   	freeNode(&N);
}

// deleteBack()
// Deletes element at back of L
// Pre: !isEmpty(L)
void deleteBack(List L)
{
        Node N = NULL;

        if( L==NULL )
        {
                fprintf(stderr, "Queue Error: calling deleteFront() on NULL List reference\n");
                exit(1);
        }
        if( isEmpty(L) )
        {
                fprintf(stderr, "List Error: calling deleteFront on an empty List\n");
                exit(1);
        }
        N = L->back;
	if( L->cursor == L->back )
	{
		L->index = -1;
		L->cursor = NULL;
	}
        if( length(L)>1 )
        {
                L->back = L->back->prev;
        }
        else
        {
                L->front = L->back = NULL;
        }
        L->length--;
        freeNode(&N);
}

// delete()
// Deletes element at cursor
// Pre: !isEmpty(L), cursor not null
void delete(List L)
{
	Node N = NULL;
	if( L==NULL )
	{
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	if( isEmpty(L) )
	{
		fprintf(stderr, "List Error: calling delete() on empty List\n");
		exit(1);
	}
	if( L->cursor == NULL )
	{
		fprintf(stderr, "List Error: calling delete() with a null cursor\n");
		exit(1);
	}
	N = L->cursor;
	if( length(L)>1 )
	{
		if(N == L->front)
		{
			(N->next)->prev = NULL;
			L->front = N->next;
		}
		else if( N==L->back)
		{
			(N->prev)->next = NULL;
			L->back = N->prev;
		}
		else
		{
			(N->prev)->next = N->next;
			(N->next)->prev = N->prev;
		}
	}
	else
	{
		L->front = L->back = L->cursor = NULL;
	}
	L->index = -1;
	L->length--;
	freeNode(&N);
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L)
{
   	Node N = NULL;

   	if( L==NULL )
	{
      		fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
      		exit(1);
   	}

   	for(N = L->front; N != NULL; N = N->next)
	{
      		fprintf(out, "%d ", N->data);
   	}
}

// copyList()
// Makes a copy of the list
List copyList(List L)
{
	if( L==NULL )
	{
		fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
		exit(1);
	}
	Node N = L->front;
	List M = newList();
	while( N!=NULL )
	{
		append(M, N->data);
		N = N->next;
	}
	return M;
}

