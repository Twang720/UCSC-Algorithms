#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main()
{
	List A = newList();
	prepend(A, 0);
	printList(stdout, A);
	printf("\n");
	moveFront(A);
	printf("%d\n", index(A));
	insertAfter(A, 2);
	printList(stdout, A);
	printf("\n");
	moveBack(A);
	printf("%d\n", index(A));
	movePrev(A);
	printf("%d\n", index(A));
	moveFront(A);
	printf("%d\n", index(A));
	List B = newList(21);	

}
