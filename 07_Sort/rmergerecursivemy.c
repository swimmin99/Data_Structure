#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
typedef struct element* elementPointer;
typedef struct element {
	int key;
} element;

int rmergeSort(element original[], int link[], int left, int right);
int listMerge(element original[], int link[], int start1, int start2);

int main() {
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+"))) {
		fprintf(stderr, "File open failure");
		exit(EXIT_FAILURE);
	}
	int size = 1, startindex;
	element arr[MAX_SIZE];
	int link[MAX_SIZE] = { 0 };
	while (!feof(fp)) {
		fscanf(fp, "%d", &arr[size++].key);
	}

	startindex = rmergeSort(arr, link, 1, size - 1);

	for (startindex; link[startindex]; startindex = link[startindex]) {
		printf("%d ", arr[startindex].key);
	}

	fclose(fp);
	return 0;
}

int rmergeSort(element original[], int link[], int left, int right) {
	if (left >= right)
			return left;
	int mid = (left + right) / 2;
	return listMerge(original, link, rmergeSort(original, link, left, mid), rmergeSort(original, link, mid + 1, right));
}

int listMerge(element original[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
		for(last1=start1, last2 = start2; last1 && last2;)
			if (original[last1].key <= original[last2].key) {
				link[lastResult] = last1;
				lastResult = last1; last1 = link[last1];
			}
			else {
				link[lastResult] = last2;
				lastResult = last2; last2 = link[last2];
			}
		if (last1 == 0)
			link[lastResult] = last2;
		else
			link[lastResult] = last1;

		return link[0];


}