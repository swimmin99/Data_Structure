#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	int key;
	char name[10];
	int grade;
} node;

void insert(node e, node a[], int i);
void insertionSort(node a[], int n);

int main() {

	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+")))
		exit(0);
	int size;

	fscanf(fp, "%d", &size);

	nodePointer head = (nodePointer)malloc(sizeof(*head) * (size+1));
	int i = 1;
	while (!feof(fp)) {
		fscanf(fp, "%d %s %d", &head[i].key, &head[i].name, &head[i].grade);
		i++;
	}

	insertionSort(head, size);
	for (int i = 1; i < size + 1; i++) {
		printf("%d %s %d\n", head[i].key, head[i].name, head[i].grade);

	}

	fclose(fp);
	free(head);

	return 0;
}


void insert(node e, node a[], int i) {

	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

void insertionSort(node a[], int n) {
	int j;
	for (j = 2; j <= n; j++) {
		node temp = a[j];
		insert(temp, a, j - 1);
	}
}
