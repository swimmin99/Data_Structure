#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50 
#define MALLOC(p,s) if (! ( (p) = malloc (s) ) ) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}

typedef enum
{head, entry} tagfield;
typedef struct matrixNode* matrixPointer;

typedef struct entryNode
{
	int row;
	int col;
	int value;

} entryNode;

typedef struct matrixNode {
	matrixPointer down;
	matrixPointer right;
	tagfield tag;
	union {
		matrixPointer next;
		entryNode entry;
	} u;
};

matrixPointer hdnode[MAX_SIZE];

matrixPointer newNode();
matrixPointer mread(void);
void mwrite(matrixPointer head);
void merase(matrixPointer* head);
void mprint(matrixPointer head);

int main() {

	int input;
	matrixPointer head = NULL;
	puts("===============SPARCE MATRIX===================");
	while (1) {
		printf("matrix menu (1. input 2. delete 3. print list 4. print matrix 5. exit) : ");
		scanf("%d", &input);
		switch(input) {
		case 1: head = mread(); break;
		case 2: if (head) merase(&head); else puts("empty list"); break;
		case 3: if (head) mwrite(head); else puts("empty list"); break;
		case 4: if (head) mprint(head); else puts("empty list"); break;
		case 5: if (head)  merase(&head); exit(1);
		default: puts("wrong input"); break;
		}
	}

	return 0;
}



matrixPointer newNode() {
	matrixPointer temp;
	MALLOC(temp, sizeof(*temp));
	return temp;
}

matrixPointer mread(void) {
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrixPointer temp, last, headnode;
	printf(" Enter number of rows, number or colums, number of nonzero terms\n");
	scanf("%d%d%d", &numRows, &numCols, &numTerms);
	numHeads = (numCols > numRows) ? numCols : numRows;

	headnode = newNode();
	headnode->tag = entry;
	headnode->u.entry.row = numRows;
	headnode->u.entry.col = numCols;

	if (!numHeads) headnode->right = head;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = newNode();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0];
		for (i = 0; i < numTerms; i++) {
			printf(" TYPE : ROW COL VALUE \n");
			scanf("%d %d %d", &row, &col, &value);
			if (row > currentRow) {
				last->right = hdnode[currentRow];
				currentRow = row;
				last = hdnode[row];
			}
			temp = newNode();
			(*temp).tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;

			last->right = temp;
			last = temp;

			hdnode[col]->u.next->down = temp;
		}
		last->right = hdnode[currentRow];
		for (i = 0; i < numCols; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < numHeads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numHeads - 1]->u.next = head;
		headnode->right = hdnode[0];
	}
	return headnode;
}
void mwrite(matrixPointer head) {
	int i;
	matrixPointer temp, headcomp = head->right;
	printf("\n numRows = %d, numCols = %d \n", head->u.entry.row, head->u.entry.col);
	printf(" The matrix by row, column, and value: \n\n");
	for (i = 0; i < head->u.entry.row; i++) {
		for (temp = headcomp->right; temp != headcomp; temp = temp->right)
			printf("%5d%5d%5d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		headcomp = headcomp->u.next;
	}
}


void mprint(matrixPointer head) {
	int i, j;
	matrixPointer temp, headcomp = head->right;
	int row = head->u.entry.row, col = head->u.entry.col;

	int** matrix;
	MALLOC(matrix, sizeof(int*) * row);
	for (int i = 0; i < row; i++) {
		matrix[i] = (int*)calloc(col, sizeof(int));
		if(!matrix[i]){fprintf(stderr, "memory error"); exit(EXIT_FAILURE); };
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d  ", matrix[i][j]);
		}
		printf("\n");
	}
	//GET SPARSE MATRIX
	printf("==========<MATRIX>==========\n");
	for (i = 0; i < row; i++) {
		for (temp = headcomp->right; temp != headcomp; temp = temp->right){	
			matrix[temp->u.entry.row][temp->u.entry.col] = temp->u.entry.value;
		}
		headcomp = headcomp->u.next;
	}
	//print
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d  ", matrix[i][j]);
		}
		printf("\n");
	}
	//free
	for (i = 0; i < row; i++) {
		free(matrix[i]);
	}
	free(matrix);
	printf("==========================\n");
}

void merase(matrixPointer* head) {
	matrixPointer temp, nodemark, headcomp = (*head)->right;
	int i, numHeads;
	for (i = 0; i < (*head)->u.entry.row; i++) {
		nodemark = headcomp->right;
		while (nodemark != headcomp) {
			temp = nodemark; nodemark = nodemark->right; free(temp);
		}
		temp = headcomp; headcomp = headcomp->u.next; free(temp);
	}

	nodemark = head;
	while (nodemark != *head) {
		temp = nodemark; nodemark = nodemark->u.next; free(temp);
	}
	free(*head); *head = NULL;

}

