#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

#define MALLOC(p,s) \
if (! ( (p) = malloc (s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}

typedef struct node* nodePointer;
typedef struct node {
	int key;
} node;

void quickSort(node a[], int left, int right) {
	int pivot, i, j; node temp;
	if (left < right) {
		i = left; j = right + 1;
		pivot = a[left].key;
		do {
			do { i++; }
			while (a[i].key < pivot);
			do { j--; }
			while (a[j].key > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}


int main() {
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	int size = 0, temp;
	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		size++;
	}

	rewind(fp);
	nodePointer head;
	MALLOC(head, sizeof(node) * (size+1));
	for (int i = 1; i < size+1; i++) {
		fscanf(fp, "%d", &head[i].key);
	}
	quickSort(head, 1, size);

	for (int i = 1; i < size+1; i++) {
		printf("%d ", head[i].key);
	}

	fclose(fp);
	return 0;
}