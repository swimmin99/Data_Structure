#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
};


nodePointer  attach(nodePointer head, int** arr, int headnum);
int** make2dArray(int rows, int cols);
void print2darr(int** a, int rows, int cols);
void init2darr(int** a, int rows, int cols);
nodePointer newNode();

int main() {
	int** arr;
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+")))
		exit(0);
	int headnum;

	fscanf(fp, "%d", &headnum);
	arr = make2dArray(headnum, headnum);

	nodePointer head;
	head = malloc(sizeof(nodePointer) * headnum);




	init2darr(arr, headnum, headnum);

	int input;
	for (int i = 0; i < headnum; i++) {
		int j = i+ 1;
		for (j; j < headnum; j++) {
			fscanf(fp, "%d", &input);
			arr[i][j] = input;
			arr[j][i] = input;
		}

	}

	nodePointer result;
	result = attach(head, arr, headnum);

	for (int i = 0; i < headnum; i++) {
		 printf("Vertex %d : ", i);
		for (; result[i].link; result[i].link = result[i].link->link)
			printf("%d ", result[i].link->data);
		if (result[i].link->link == NULL);
		puts(" ");

	}


	fclose(fp);
	return 0;
}

nodePointer attach(nodePointer head, int** arr, int headnum) {
	nodePointer rear;
	for (int i = 0; i < headnum; i++) {
		rear = NULL;
		int j = i;

		while(1){
			if (arr[i][j] == 1) {
				nodePointer temp = newNode();
				if (!rear)
					head[i].link = temp;
				if (rear) {
					rear->link = temp;
				}
				temp->data = j;
				temp->link = NULL;
				rear = temp;
			}j++; 
			if (j == headnum)
				j = 0;

			if (j == i)
				break;

		}

	}

	return head;
}

int** make2dArray(int rows, int cols) {

	int** x = (int**)malloc(sizeof(int*) * rows);

	for (int i = 0; i < rows; i++)
		x[i] = (int*)malloc(sizeof(int) * cols);

	return x;

}

void print2darr(int** a, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		printf("\n");
		for (j = 0; j < cols; j++)
			printf("%d ", a[i][j]);
	}
}

void init2darr(int** a, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++)
			a[i][j] = 0;
	}
}

nodePointer newNode() {
	nodePointer temp = malloc(sizeof(*temp));
	return temp;
}
