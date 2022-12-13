#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p) = malloc(s))) {fprintf(stderr, "memory failed"); exit(EXIT_FAILURE);}
typedef struct node* nodePointer;
typedef struct node {
	int key;
	nodePointer rightChild, leftChild;
} node;
void attach(nodePointer temp, nodePointer root);
void printinorder(nodePointer root);
void freetree(nodePointer root);


nodePointer newNode() {
	nodePointer temp = NULL;
	MALLOC(temp, sizeof(*temp));
	return temp;
}

int main() {
	FILE* fp;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "FILE open failed");
		exit(EXIT_FAILURE);
	}
	int size;
	nodePointer head = NULL;
	fscanf(fp, "%d", &size);
	while (!feof(fp)) {
		nodePointer temp = newNode();
		fscanf(fp, "%d", &temp->key);
		temp->rightChild = NULL;
		temp->leftChild = NULL;
		attach(temp, &head);
	}

	printinorder(head);
	
	fclose(fp);
	freetree(head);


	head = NULL;


	return 0;
}

void attach(nodePointer item, nodePointer * node) {
	nodePointer temp = *node;
	if (*node) {
			
		if ((*node)->key < item->key) {
			while ((*node)->rightChild) {
				(*node) = (*node)->rightChild;
			}
			(*node)->rightChild = item;
		}
		else if ((*node)->key > item->key) {
			while ((*node)->leftChild) {
				(*node) = (*node)->leftChild;
			}
			(*node)->leftChild = item;

		}

		*node = temp;
	}
	else
		*node = item;

}

void printinorder(nodePointer root) {
	if (root) {
		printinorder(root->leftChild);
		printf("%d", root->key);
		printinorder(root->rightChild);
	}
}

void freetree(nodePointer root) {
	if (root) {
		freetree(root->leftChild);
		freetree(root->rightChild);
		free(root);
	}
}