//input size is not fixed, but limit must be set in MAX_INPUT_SIZE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define CALLOC(p, c, s) if(!((p) = calloc((c),(s)))){fprintf(stderr, "CALLOC FAILED"); exit(EXIT_FAILURE);}
#define MALLOC(p,s) \
if (! ( (p) = malloc (s) ) ) { \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE);\
}
#define DIGITNUM 26
#define MAX_INPUT_SIZE 10
//lower case alphabet num
typedef struct element* elementPointer;
typedef struct element {
	char string[MAX_INPUT_SIZE];
} element;

int digit(element a, int j, int r, int d);
int radixSort(element a[], int link[], int d, int r, int n);

int main() {

	int link[100];
	int r = DIGITNUM;
	element head[100];
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+")))
		exit(0);

	int size = 1, maxlen = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s", head[size].string);
		if (strlen(head[size].string) > maxlen)
			maxlen = strlen(head[size].string);
		size++;
	}

	int index;
	index = radixSort(head, link, maxlen, r, size - 1);

	for (int i = 1; i < size; i++) {
				printf("%s", head[index].string);
		printf(" ");
		index = link[index];
	}


	fclose(fp);
	return 0;
}

int digit(element a, int j, int r, int d) {
	int num = a.string[j];
	if (95 > num || num > 123)
		num = 0;
	else
		num -= 97;

	return num;
}

int radixSort(element a[], int link[], int d, int r, int n) {
	//d is digit r is key number n is zie
	int* front;
	int* rear;
	CALLOC(front, r, sizeof(int));
	CALLOC(rear, r, sizeof(int));
	int i, bin, current, first, last;
	first = 1;
	for (i = 1; i < n; i++) {
		link[i] = i + 1;
	}
	link[n] = 0;

	for (i = d - 1; i >= 0; i--) {
		for (bin = 0; bin < r; bin++)
			front[bin] = 0;
		for (current = first; current; current = link[current]) {
			bin = digit(a[current], i, r, d);
			if (front[bin] == 0)
				front[bin] = current;
			else
				link[rear[bin]] = current;
			rear[bin] = current;
		}
		for (bin = 0; !front[bin]; bin++);
		first = front[bin];
		last = rear[bin];

		for(bin++; bin<r; bin++)
			if (front[bin]) {
				link[last] = front[bin];
				last = rear[bin];
			}
		link[last] = 0;
	}
	free(front);
	free(rear);
	return first;

}