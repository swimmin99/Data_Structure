//input : in.txt / strings size of three seperated by blank space or enter
//search input : search.txt / strings size of three seperated by blank space or enter
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define STRING_LENGTH 4
#define MALLOC(p,s) if (! ( (p) = malloc (s) ) ) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}
#define CALLOC(p,c,s) if (! ( (p) = calloc (c, s) ) ) {fprintf(stderr, "Insufficient memory");exit(EXIT_FAILURE);}

typedef struct node* nodePointer;
typedef struct node {
	int num;
	nodePointer link;
	char data[STRING_LENGTH];
} node;

int hashfunction(char k[]);
int stringtoint(char* key);
void searchht(FILE* fp2, char ht[]);
void printht(int d, char ht[]);

int main() {
	int d;
	scanf("%d", &d);
	nodePointer* ht;
	CALLOC(ht, d, sizeof(*ht));




	FILE* fp1, * fp2;
	if (!(fp1 = fopen("in.txt", "r+"))) { fprintf(stderr, "input file open failure"); exit(EXIT_FAILURE); }
	if (!(fp2 = fopen("search.txt", "r+"))) { fprintf(stderr, "sarch file open failure"); exit(EXIT_FAILURE); }


	while (!feof(fp1)) {
		nodePointer newnode, temp;
		MALLOC(newnode, sizeof(*temp));
		fscanf(fp1, "%s", newnode->data);
		newnode->num = stringtoint(newnode->data);
		newnode->link = NULL;
		int num = hashfunction(newnode->data);

		if (!ht[num])
			ht[num] = newnode;
		else {
			for (temp = ht[num]; temp->link; temp = temp->link);
			temp->link = newnode;
		}

	}



	printf("\n");

	searchht(fp2, ht);
	printht(d, ht);

	fclose(fp1);
	fclose(fp2);
	return 0;




	return 0;
}

int stringtoint(char* key) {
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

int hashfunction(char k[]) {
	int index;
	index = stringtoint(k) % 5;

	return index;
}

void searchht(FILE * fp2, nodePointer ht[]) {

	while (!feof(fp2)) {
		nodePointer search, temp;
		MALLOC(search, sizeof(*search));
		fscanf(fp2, "%s", search->data);
		search->num = stringtoint(search->data);
		search->link = NULL;
		int num = hashfunction(search->data);

		if (ht[num]) {
			for (temp = ht[num]; temp; temp = temp->link) {
				if (strcmp(temp->data, search->data) == 0) {
					puts("S");
				}
				else if (strcmp(temp->data, search->data) != 0 && !temp->link)
					puts("E");
			}
		}
		else
			puts("E");
	}
}

void printht(int d, nodePointer ht[]) {
	for (int i = 0; i < d; i++) {
		printf("%d : ", i);
		for (nodePointer temp = ht[i]; temp; temp = temp->link) {
			printf("%s (%d)|", temp->data, temp->num);
		}
		printf("\n");
	}
}