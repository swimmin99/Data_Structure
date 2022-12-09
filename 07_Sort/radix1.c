#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define CALLOC(p, c, s) if(!((p) = calloc((c),(s)))){fprintf(stderr, "CALLOC FAILED"); exit(EXIT_FAILURE);}
#define DIGITNUM 10

typedef struct element* elementPointer;
typedef struct element {
	int key;
} element;


int radixSort(element a[], int link[], int d, int r, int n);
int digit(element a, int j, int r, int d);
int main() {

	int link[100];
	int r = DIGITNUM;
	FILE* fp = NULL;
	if (!(fp = fopen("in.txt", "r+")))
		exit(0);

	int max;
	int digit = 0;
	int size = 1;
	int first;
	element head[100];

	fscanf(fp, "%d", &max);
	head[size++].key = max;

	while (!feof(fp)) {
		fscanf(fp, "%d", &head[size++].key);
		if (head[size-1].key > max)
			max = head[size-1].key;
	}
	while (max > 0) {
		max /= 10;
		digit++;
	}

	first = radixSort(head, link, digit, r, size-1);

	for (int i = 1; i < size; i++) {
		printf("%d  ", head[first]);
		first = link[first];
	}

	fclose(fp);
	return 0;
}

int digit(element a, int j, int r, int d) {
	int* arr;
	int num = a.key;
	CALLOC(arr, d - 1, sizeof(int));
	int i = 0;
	while (num > 0 && d >= 0) {
		arr[--d] = num % 10;
		num /= r;
	}

	return arr[j];
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