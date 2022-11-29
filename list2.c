//list2.c
//PROBLEM : Need to sort (in increasing order) a linkded list during insertion
//CONDITION : Do not use additional function to get position to insert, Do not initiate first(head node) as global variable, Duplicate value must be eradicated before adding
//INPUT : .txt/int/ex) 10 20 35
//ADT : insert/position/print/delete
//=======================================================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(first) (!(first))
#define MALLOC(p,s) if (!((p) = malloc(s))) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;


void delete2(listPointer *first, listPointer trail, listPointer x) {
	if (trail)
		trail->link = x->link;
	else
		(*first) = (*first)->link;
	free(x);
}


void insert(listPointer *first, int n) {

	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = n;
	listPointer search, trail;
	trail = NULL;
	int flag = 1;

	for (search = (*first); ; search = search->link) {
		if (!search) {
			break;
		}
		else {
			if (search->data > n) {
				break;
			}
			else if (search->data == n) {
				delete2(first, trail, search);
				break;
			}
		}
		trail = search;
	}


	if (trail) {
		temp->link = trail->link;
		trail->link = temp;
	}
	else {
		temp->link = (*first);
		(*first) = temp;
	}
}

void printList(listPointer first) {
	printf("The list contatins: ");
	listPointer search = first;

	for (; search; search = search->link) {
		printf("%d ", search->data);
	}
	printf("\n");
}


int main() {
	listPointer first = NULL;
	//======================= FILE OPEN ====================//
	char filename[100];
	printf("Input filename : ");
	gets(filename);
	FILE* fp = NULL;
	if (!(fp = fopen(filename, "r+"))) {
		fprintf(stderr, "File open failed");
		exit(EXIT_FAILURE);
	}

	//====================== FILE READ ======================//
	int n1;

	while (!feof(fp)) {
		int n;
		fscanf(fp, "%d", &n);
		insert(&first, n);
		printList(first);
	}

	//====================== INSERT ==========================//
	int input;

	while (1) {
		scanf("%d", &input);
		if (input == -1)
			break;
		insert(&first, input);
		printList(first);
	}

	//====================== FREE ==========================//
	while (first != NULL) {
		delete2(&first, NULL, NULL);
	}

	fclose(fp);
	return 0;
}
