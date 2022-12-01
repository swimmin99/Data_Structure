//heaptree.c
//CONDITION : heap tree / heap array init : global, static /
//INPUT : file (.txt)/ consists of two line -> first line : list, second line : n of nodes to delete
//ADT : pusy, pop, print
//=======================================================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define MAX_ELEMENTS 50
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n);
element pop(int* n);
void print();
void printtree(int count);

int main() {
	int count;

	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		puts("File open failed");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d", &count);
	int input = 0, i = 0;
	while (i < count) {
		fscanf(fp, "%d", &input);
		element temp;
		temp.key = input;
		push(temp, &n);
		i++;
	 }

	int repeat = 0;
	fscanf(fp, "%d", &repeat);
	for (; repeat > 0; repeat--) {
		pop(&n);
	}

	print();

	return 0;
}

void push(element item, int* n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.");
		exit(EXIT_FAILURE);
	}

	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int* n) {

	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n))
			if ((child < *n) && (heap[child].key < heap[child + 1].key))
				child++;
		if (temp.key >= heap[child].key)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;

}

void print() {
	if (n == 0) return;
	int i = 1;
	while (i <= n) {
		printf("%d ", heap[i++].key);
	}
}
