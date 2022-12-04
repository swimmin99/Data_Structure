#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)if(!((p) = malloc((s)))){fprintf(stderr, "MALLOC ERROR"); exit(EXIT_FAILURE);}
#define MAXSTACKS 10

typedef struct {
	int key;
} element;

typedef struct stack* stackPointer;

typedef struct stack {
	element data;
	stackPointer link;
};

stackPointer top[MAXSTACKS];

void push(int i, element item)
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top[i];
	top[i] = temp;
}

element pop(int i) {
	stackPointer temp = top[i];
	element item;
	if (!temp) {
		fprintf(stderr, "stack empty");
		exit(1);
	}
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;
}

int main() {

	puts("Enter the number of elements to push");
	int repeat;
	scanf("%d", &repeat);
	int num = 0;
	while (repeat > 0) {
		element temp;
		printf("Enter a b a: stack array index, eb : lement data\n");
		scanf("%d %d", &num, &temp.key);
		push(num, temp);
		repeat--;
	}
	num = 0;
	puts("Enter the number of elements to pop");
	scanf("%d", &repeat);
	while (repeat>0) {
		printf("Enter n : stack array index\n");
		scanf("%d", &num);
		printf("%d", pop(num).key);
		repeat--;
	}

	return 0;
}