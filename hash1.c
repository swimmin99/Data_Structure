//input : in.txt / strings size of three seperated by blank space or enter
//search input : search.txt / strings size of three seperated by blank space or enter
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define STRING_LENGTH 4
#define CALLOC(p,c,s) \
if (! ( (p) = calloc (c, s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}

#define MALLOC(p,s) \
if (! ( (p) = malloc (s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}

char* search(char k[], char** ht, int b);
int hf(char k[]);
int stringtoint(char* key);

int main() {
	int d;
	scanf("%d", &d);
	char** ht;
	MALLOC(ht, sizeof(*ht) * d);
	for (int i = 0; i < d; i++) {
		CALLOC(ht[i], STRING_LENGTH, sizeof(char));
	}

	FILE* fp1, * fp2;
	if (!(fp1 = fopen("in.txt", "r+"))) { fprintf(stderr, "input file open failure"); exit(EXIT_FAILURE); }
	if (!(fp2 = fopen("search.txt", "r+"))) { fprintf(stderr, "sarch file open failure"); exit(EXIT_FAILURE); }

	int i = 0;
	char temp[4], * temp2;
	int numtemp;

	while (!feof(fp1)) {
		fscanf(fp1, "%s", temp);
		numtemp = hf(temp);

		if (!(*ht[numtemp])) {
			strcpy(ht[numtemp], temp);
		}
		else {
			puts("over flow occured");

			if (temp2 = search(temp, ht, d))
				strcpy(temp2, temp);
			else {
				puts("hash table is full");
				exit(EXIT_FAILURE);
			}
		}


	}

	while (!feof(fp2)) {
		fscanf(fp2, "%s", temp);
		if (strcmp(ht[hf(temp)], temp) == 0) {
			puts("S");
		}
		else {
			int signal = 0;
			for (int i = 0; i < d; i++) {
				if (strcmp(ht[i], temp) == 0) {
					puts("S");
					signal = 1;
				}
			}
			if (signal == 0)
				puts("E");
		}
	}


	printf("\n");

	for (int i = 0; i < d; i++) {
		printf("%d : %s (%d)\n", i, ht[i], stringtoint(ht[i]));
	}

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

int hf(char k[]) {
	int index;
	index = stringtoint(k) % 5;

	return index;
}

char* search(char k[], char** ht, int b) {
	int homeBucket, currentBucket;
	homeBucket = hf(k);
	for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket] != k;) {
		currentBucket = (currentBucket + 1) % b;
		if (!(*ht[currentBucket]))
			return ht[currentBucket];
		if (currentBucket == homeBucket)
			return NULL;
	}
	return NULL;

}