//INPUT : .txt/int/ex) 10 20 35
//PROBLEM : Need to sort a list during insertion (!do not use rear!)
//ADT : insert/position/print/delete
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(first)(!(first))
#define MALLOC(p,s) if (! ( (p) = malloc (s) ) ) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};

listPointer position(listPointer first, int n) {
	if (!first)//in case first is NULL return NULL
		return NULL;
	else {
		for (;; first = first->link) {
			// in case the node is bigger than input n
			if (first->data > n)
				return NULL;
			// in case the node is same as input n 
			if (first->data == n) {
				return first;
			}
			// in case the node is the last node
			if (!(first->link))
				return first;
		}
	}
}



void insert(listPointer* first, listPointer x, int n) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = n;
	
	//1. first exists and following node is NULL
	//2. first exites and followin node is not NULL
	//3. first is NULL;
	if (*first) {
		if (x == NULL) {
			temp->link = *first;
			*first = temp;
		}
		else {
			temp->link = x->link;
			x->link = temp;
		}

	} else {
		temp->link = NULL;
		*first = temp;
	}
}

void printList(listPointer first) {
	printf("The list contains: ");
	for (; first; first = first->link) {
		printf("%4d", first->data);
	}
	printf("\n");
}

void delete(listPointer* first, listPointer trail, listPointer x) {
	if (trail)
		trail->link = x->link;
	else
		*first = (*first)->link;
	free(x);
}


int main() {

	listPointer first = NULL;
	//======================FILE OPEN====================//
	char filename[100];
	printf("input filename : ");
	gets(filename);
	FILE* fp = NULL;
	if (!(fp = fopen(filename, "r+"))) {
		fprintf(stderr, "File open failed");
		exit(EXIT_FAILURE);
	}
	//======================FILE READ=========================//
	int n1;

	while (!feof(fp)) {
		int n;
		fscanf(fp, "%d", &n);
		insert(&first, position(first, n), n);
		printList(first);
	}

	//===================INSERTION=============================//

	int input = 0;

	while (1) {
		scanf("%d", &input);
		if (input == -1)
			break;
		insert(&first, position(first, input), input);
		printList(first);
	}

	while (first != NULL) {
		delete(&first, NULL, NULL);
	}

	fclose(fp);
	return 0;
}

//===================position alternative=============================//
/*
listPointer position(listPointer first, int n)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp = NULL;
	for (; first; first = first->link) {

		if (first->data > n)
			return temp;

		else if (first->data == n)
			return first;

		temp = first;


		if (first->link == NULL)
			return first;
	}
}
*/