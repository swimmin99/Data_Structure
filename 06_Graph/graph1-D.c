//undirected adjacency graph
// condition : adjacency matrix and nod head should be allocated statically
//input via file(.txt)
//ADT : attach, newNode
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) if(!((p) = malloc(s))){fprintf(stderr, "Memory failed"); exit(EXIT_FAILURE);}
typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

void attach(node head[], int arr[][10], int num);
nodePointer newNode();
int main () {
	int arr[10][10] = {0};
	int num;
	node head [100];
	nodePointer result;
	
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "File open failed");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d", &num);

	int input;
	for (int i = 0; i < num; i++) {
		int j = i + 1;
		for (j; j < num; j++) {
			fscanf(fp, "%d", &input);
			arr[i][j] = input;
			arr[j][i] = input;
		}
	}

	attach(head, arr, num);

	for (int i = 0; i < num; i++) {
		printf("Vertex %d : ", i);
		for (; head[i].link; head[i].link = head[i].link->link)
			printf("%d ", head[i].link->data);
		if (head[i].link->link == NULL);

		puts(" ");
	}

	fclose(fp);
	
	return 0;


}

void attach(node head[], int arr[][10], int num) {
	nodePointer rear;
	for (int i = 0; i < num; i++) {
		rear = NULL;
		int j = i;

		while (1) {
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

			if (j == num)
				j = 0;
			if (j == i)
				break;


		}
	}

}


nodePointer newNode() {
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));
	return temp;
}

