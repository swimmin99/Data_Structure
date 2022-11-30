//List4.c
//PROBLEM : Doubly linked list with a Menu
//INPUT : .txt file for a initial list, stdin for input
//ADT : insert/delete/createNode/printList/position/search/menu
//=======================================================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
};




void dinsert(nodePointer node, nodePointer newnode);
void ddelete(nodePointer node, nodePointer deleted);
nodePointer createNode();
void printorderlist(nodePointer node);
void printreverselist(nodePointer node);




void menu(nodePointer* head);
void fileopen(nodePointer* head);
void menuinsert(nodePointer head);
nodePointer position(nodePointer head, int num);
void searchprint(nodePointer node, nodePointer* head, int num);
void searchmenu(nodePointer head);
void searchdelete(nodePointer node, nodePointer* head, int num);
void deletemenu(nodePointer head);

int main(void) {
	nodePointer head = createNode();
	head->rlink = NULL;



	menu(head);



	return 0;
}

///////menurelatedfunc

void menu(nodePointer head) {

	int input = 0;
	while (input != 5) {
		printf("MENU (1. Load File 2. Insert 3. Search Index 4. Delete 5. EXIT) >>");
		scanf("%d", &input);
		switch (input) {
		case 1: fileopen(head); break;
		case 2: if (head->rlink == NULL) { puts("open file first"); break; }menuinsert(head); break;
		case 3: if (head->rlink == NULL) { puts("open file first"); break; }searchmenu(head); break;
		case 4: if (head->rlink == NULL) { puts("open file first"); break; }deletemenu(head); break;
		case 5: if (head->rlink != NULL) {//free
			while (head->rlink != head) {
				ddelete(head, head->llink);
			};
		} free(head); head = NULL;
		exit(0);
		default: puts("wrong input"); break;
		}

		if (head->rlink != NULL && head->rlink != head)
			printorderlist(head);
		if (head->rlink == head)
			puts("empty");

		printf("\n");
	}
}


void fileopen(nodePointer head) {
	FILE* fp = NULL;
	char filename[100];
	getchar(" ");
	gets(filename);


	if ((fp = fopen(filename, "r+")) == NULL) { puts("file open failure"); exit(EXIT_FAILURE); }
	int num;

	head->llink = head, head->rlink = head;
	head->data = NULL;


	while (!feof(fp)) {
		nodePointer temp = createNode();
		fscanf(fp, "%d", &temp->data);
		dinsert(head->llink, temp);
	}

	fclose(fp);

}

void menuinsert(nodePointer head) {
	nodePointer temp = createNode();
	printf("Enter>>");
	int num;
	scanf("%d", &num);
	temp->data = num;
	dinsert(position(head, num), temp);
}


nodePointer position(nodePointer head, int num) {
	nodePointer temp = createNode();
	temp = head;

	while (temp->rlink != head) {
		if (temp->rlink->data > num)
			return temp;
		else
			temp = temp->rlink;

	}
	return temp;

}



void searchmenu(nodePointer head) {
	int input;
	printf("Enter >>");
	scanf("%d", &input);
	searchprint(head, head, input);
}

void searchprint(nodePointer node, nodePointer* head, int num) {
	int count = 0;
	while (1) {

		if (node->data == num) {
			printf("%d\n", count);
			break;
		}
		node = node->rlink;
		if (node->data == NULL) {
			puts("invalid");
			break;
		}
		count++;
	}

}

void deletemenu(nodePointer head) {
	int input;
	printf("Enter >>");
	scanf("%d", &input);
	searchdelete(head, head, input);
}


void searchdelete(nodePointer node, nodePointer* head, int num) {
	int count = 0;
	while (1) {
		if (node->data == num) {
			ddelete(head, node);
			break;
		}
		node = node->rlink;
		if (node->data == NULL) {
			puts("invalid");
			break;
		}
		count++;
	}

}

///////////////////listbasicfunc


void dinsert(nodePointer node, nodePointer newnode)
{ /* insert newnode to the right of node */

	newnode->llink = node;
	newnode->rlink = node->rlink;
	node->rlink->llink = newnode;
	node->rlink = newnode;
}

void ddelete(nodePointer node, nodePointer deleted)
{ /* delete from the doubly linked list */
	if (node == deleted)
		printf("Deletion of head node not permitted.\n");
	else {
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}
}

nodePointer createNode() {
	nodePointer temp = (nodePointer)malloc(sizeof(*temp));
	return temp;
}

void printorderlist(nodePointer node) {
	nodePointer temp = node;
	while (1) {
		temp = temp->rlink;
		printf("%d ", temp->data);
		if (temp->rlink == node)
			break;
	}
}

void printreverselist(nodePointer node) {
	nodePointer temp = node;
	while (1) {
		temp = temp->llink;
		printf("%d ", temp->data);
		if (temp->llink == node)
			break;
	}
}