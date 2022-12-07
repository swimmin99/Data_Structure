#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(first) (!(first))
#define MALLOC(p,s) if (!((p) = malloc(s))) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}
#define MAX_QUEUE_SIZE 20
#define Q_FULL(n) (n==MAX_QUEUE_SIZE-1)
#define Q_EMPTY(front, rear) (front > rear)
typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
};
treePointer queue[MAX_QUEUE_SIZE] = {0};
int rear = 0;
int front = 0;


void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
void addq(treePointer item);
treePointer deleteq();
void levelOrder(treePointer ptr);
treePointer newNode();
void insert(treePointer ptr, FILE* fp);

void freelist(treePointer ptr) {
	if (ptr) {
		freelist(ptr->leftChild);
		freelist(ptr->rightChild);
		treePointer temp;
		temp = ptr;
		free(temp);
	}
}

int main() {
	FILE* fp;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "error");
		exit(1);
	}
	treePointer head;
	MALLOC(head, sizeof(*head));
	head->leftChild = NULL;
	head->rightChild = NULL;
	fscanf(fp, "%d", &head->data);


	insert(head, fp);
	printf("preorder : ");
	preorder(head);
	puts(" ");
	printf("inorder : ");
	inorder(head);
	puts(" ");
	printf("postorder : ");
	postorder(head);
	puts(" ");
	printf("levelorder : ");
	levelOrder(head);

	fclose(fp);
	freelist(head);
	
	head= NULL;



	return 0;

}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%d ", ptr->data);
	}
}

treePointer newNode() {
	treePointer temp;
	MALLOC(temp, sizeof(*temp));

	return temp;
}

void insert(treePointer ptr, FILE* fp) {
	treePointer rear = ptr;
	while (!feof(fp))
	{
		treePointer temp;
		MALLOC(temp, sizeof(*temp));
		fscanf(fp, "%d", &temp->data);
		temp->leftChild = NULL;
		temp->rightChild = NULL;
		if (!rear->leftChild) {
			rear->leftChild = temp;
		}
		else if (!rear->rightChild && rear->leftChild) {
			rear->rightChild = temp;
			rear = rear->leftChild;
		}

	}


}

void addq(treePointer item) {
	if (Q_FULL(queue)) {
		fprintf(stderr, "q full");
	}
	queue[++rear] = item;
}

treePointer deleteq() {
	if (Q_EMPTY(front, rear)) {
		fprintf(stderr, "q empty");
			exit(EXIT_FAILURE);
	}
	
	return queue[++front];
}



void levelOrder(treePointer ptr) {
	front = 0; rear = 0;
	treePointer queue[MAX_QUEUE_SIZE];
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%d ", ptr->data);
			if (ptr->leftChild)
				addq(ptr->leftChild);
			if (ptr->rightChild)
				addq(ptr->rightChild);
		}
		else break;
	}
	
}





