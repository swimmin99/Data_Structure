#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 50
short int visited[MAX_VERTICES];

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

nodePointer newNode();
void dfs(int v, nodePointer graph[]);
void attach(nodePointer head[], int arr[][10], int headnum);

int main() {
	int adjMatr[10][10] = {0}, num;
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "File open failed");
	}
	int headnum;
	node head[10] = {0};
	fscanf(fp, "%d", &headnum);

	int input;
	for (int i = 0; i < headnum; i++) {
		int j = i + 1;
		for (j; j < headnum; j++) {
			fscanf(fp, "%d", &input);
			adjMatr[i][j] = input;
			adjMatr[j][i] = input;
		}
	}

	attach(head, adjMatr, headnum);

	scanf("%d", &num);
	printf("dfs(%d) : ", num);
	dfs(num, head);
	int i = 0;

	fclose(fp);


	return 0;
}

nodePointer newNode() {
	nodePointer temp = malloc(sizeof(*temp));
	return temp;
}

void attach(nodePointer head[], int arr[][10], int headnum) {
	nodePointer rear;
	for (int i = 0; i < headnum; i++) {
		rear = NULL;
		for (int j = 0; j < headnum; j++) {
			if (arr[i][j] == 1) {
				nodePointer temp = newNode();
				if (!rear)
					head[i] = temp;
				if (rear) {
					rear->link = temp;
				}
				temp->data = j;
				temp->link = NULL;
				rear = temp;

			}
		}
	}


	return head;
}

void dfs(int v, nodePointer graph[]) {
	nodePointer w;
	visited[v] = TRUE;
	printf(" % 5d", v);

	for (w = graph[v];; w = w->link) {
		if (!visited[w->data]) {
			dfs(w->data, graph);
		}
		if (!w->link)
			break;
	}
}

