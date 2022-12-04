#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 50
#define MALLOC(p,s) \
if (! ( (p) = malloc (s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}
short int visited[MAX_VERTICES];

typedef struct queue* queuePointer;
typedef struct queue {
	int vertex;
	queuePointer link;
};
queuePointer front, rear;


typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
} node;

nodePointer newNode();
void attach(nodePointer head[], int arr[][10], int headnum);
void bfs(int v, int graph[]);
void freelist(int headnum, nodePointer graph[]);

void addq(int i)
{/* add item to the rear of queue i */
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->vertex = i;
	temp->link = NULL;
	if (front)
		front->link = temp;
	else
		front = temp;
	rear = temp;
}

void queueEmpty() {
	puts("Queue empty");
	exit(1);
}


int deleteq()
{/* delete an element from queue i */
	queuePointer temp = front;
	int item;
	if (!temp)
		queueEmpty();
	item = temp->vertex;
	front = temp->link;
	free(temp);
	return item;
}

int main() {
	int adjMatr[10][10] = { 0 }, num, inputlist[100];
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "File open failed");
	}
	int headnum;
	nodePointer head[10] = { 0 };
	fscanf(fp, "%d", &headnum);

	int input;
	int k = 0;
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
	bfs(num, head);
	int i = 0;

	fclose(fp);
	freelist(headnum, head);

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
				if (!rear) {
					head[i] = temp;
				}
				if (rear) {
					rear->link = temp;
				}
				temp->vertex = j;
				temp->link = NULL;
				rear = temp;

			}
		}
	}


	return head;
}

void bfs(int v, nodePointer graph[])
{
	nodePointer w;
	front = rear = NULL;
	printf(" % 5d", v);
	visited[v] = TRUE;
	addq(v);
	while (front) {
		v = deleteq();
		for (w = graph[v]; w; w = w->link
			)
			if (!visited[w->vertex]) {
				printf("% 5d", w->vertex);
				addq
				(w->vertex);
				visited[w->vertex] = TRUE;
			}
	}
}


void freelist(int headnum, nodePointer graph[]) {
	nodePointer temp;
	for (int i = 0; i < headnum; i++) {
		while ((graph[i]->link)) {
			if (!(graph[i]->link->link)) {
				temp = graph[i]->link;
				graph[i]->link = NULL;
				free(temp);
			}
			if (graph[i]->link) {
				temp = graph[i]->link;
				graph[i]->link = temp->link;
				free(temp);
			}
		}
	}


}