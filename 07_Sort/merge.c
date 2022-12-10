#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
typedef struct element* elementPointer;
typedef struct element {
	int key;
} element;

void mergeSort(element original[], int arrsize);
void mergePass(element original[], element extra[], int arrsize, int segmentsize);
void merge(element original[], element extra[], int startarr1, int endofarr1, int endofarr2);

int main() {
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "File open failure");
		exit(EXIT_FAILURE);
	}
	int size = 1;
	element arr[MAX_SIZE];
	while (!feof(fp)) {
		fscanf(fp, "%d", &arr[size++].key);
	}

	mergeSort(arr, size-1);

	for (int i = 1; i < size; i++) {
		printf("%d ", arr[i].key);
	}
	fclose(fp);

	return 0;
}

void mergeSort(element original[], int arrsize) {
	int segmentsize = 1;
	element extra[MAX_SIZE];
	while (segmentsize < arrsize) {
		mergePass(original, extra, arrsize, segmentsize);
		segmentsize *= 2;
		mergePass(extra, original, arrsize, segmentsize);
		segmentsize *= 2;
	}
}




void mergePass(element original[], element extra[], int arrsize, int segmentsize) {
	int i, j;
	for (i = 1; i <= arrsize - 2 * segmentsize + 1; i += 2 * segmentsize)
		merge(original, extra, i, i + segmentsize - 1, i + 2 * segmentsize - 1);
	if ((i + segmentsize - 1) < arrsize)
		merge(original, extra, i, i + segmentsize - 1, arrsize);
	else
		for (j = i; j <= arrsize; j++)
			extra[j] = original[j];
}

void merge(element original[], element extra[], int startarr1, int endofarr1, int endofarr2) {
	int startarr2, extraindex, i;
	startarr2 = endofarr1 + 1;
	extraindex = startarr1;

	while (startarr1 <= endofarr1 && startarr2 <= endofarr2) {
		if (original[startarr1].key <= original[startarr2].key)
			extra[extraindex++] = original[startarr1++];
		else
			extra[extraindex++] = original[startarr2++];
	}
	if (startarr1 > endofarr1)
		for (i = startarr2; i <= endofarr2; i++)
			extra[i] = original[i];
	else
		for (i = startarr1; i <= endofarr1; i++)
			extra[extraindex + i - startarr1] = original[i];
	}
