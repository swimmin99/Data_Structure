//HEAP SORT
//IF YOU WISH TO OBSERVE THE PROCESS OF SORT DELETE ALL THE QUOTE SIGNS (// OR /* */)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

#define MALLOC(p,s) \
if (! ( (p) = malloc (s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}

typedef struct element* elementPointer;
typedef struct element {
	int key;
} element;


void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;

	while (child <= n) {
		if ((child < n) && (a[child].key < a[child + 1].key))
			child++;
		if (rootkey > a[child].key)
			break;
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}



void heapSort(element a[], int n) {
	int i, j;
	element temp;

	for (i = n / 2; i > 0; i--) {
//		puts(" ");
		adjust(a, i, n);
/*		for (int i = 1; i < n; i++) {
			printf("%d ", a[i].key);
		}
*/	}
/*	puts(" ");
	puts(" ");
	for (int i = 1; i < n; i++) {
		printf("%d ", a[i].key);
	}
*/
	for (i = n - 1; i > 1; i--) {
//		puts(" ");

		SWAP(a[1], a[i], temp);
		adjust(a, 1, i-1);
/*		for (int i = 1; i < n; i++) {
			printf("%d ", a[i].key);
		}
*/	}
}



int main() {
	int arr[50];
	element head [50];
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+")))
		exit(0);
	int size = 1;
	while (!feof(fp)) {
		fscanf(fp, "%d", &head[size++].key);
	}

	heapSort(head, size);
//	puts(" ");
	for (int i = size-1; i > 0; i--) {
		printf("%d ", head[i].key);
	}
	fclose(fp);
	return 0;
}
