#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200 /* maximum heap size+l */
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int key;
	/* other fields */
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n)
{/* insert item into a max heap of current size *n */
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int* n)
{
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
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void menu(FILE* fp) {
	int input;
	puts("1. 파일 입력 2. 삭제 3. 출력 4. 종료");
	scanf("%d", &input);
	switch (input) {
	case 1 : 	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "file err");
		exit(EXIT_FAILURE);
	}
		   int size;
		   fscanf(fp, "%d ", &size);


		   while (!(feof(fp))) {
			   element temp;
			   fscanf(fp, "%d ", &temp.key);
			   push(temp, &n);
		   } break;
	case 2: printf("%d : 삭제됨\n", (pop(&n).key)); break;

	case 3:	for (int i = 1; i < n + 1; i++)
		printf("%d ", heap[i]); break;
		
		
	case 4 : exit(EXIT_FAILURE);

	}

}

int main() {
	FILE* fp = NULL;
	while (1) {
		menu(fp);
	}


}