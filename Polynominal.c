#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(first)(!(first))
#define MALLOC(p,s) if (! ( (p) = malloc (s) ) ) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}
#define COMPARE(x, y)((x) < (y) ? -1 : (x) == (y) ? 0 : 1)

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
};


polyPointer insert(FILE* fp);
void printList(polyPointer first);
void delete(polyPointer* first, polyPointer trail, polyPointer x);
polyPointer padd(polyPointer poly1, polyPointer poly2);
void attach(float coefficient, int exponent, polyPointer* poly);

int main() {
	polyPointer * polynominal;
	polyPointer answ = NULL;
	int num, count = 0;
	puts("============<Polynominal Addition Calculator>================ ");
	//======================= INPUT ====================//
	puts("Enter N of polynominals : ");
	scanf("%d", &num);
	if (num < 2) {
		fprintf(stderr, "Enter integer larger than 1 ");
		exit(EXIT_FAILURE);
	}

	//======================= INSERT ====================//
	MALLOC(polynominal, sizeof(polyPointer) * num);
	while (count < num) {
		printf("POLYNOMINAL %d\n", count+1);
		*(polynominal + count) = NULL;
		(*(polynominal + count)) = insert(*(polynominal+count));
		count++;
		puts("------------------------------------------------------------ ");
	}
	//======================= PADD ====================//
	for (count = 1; count < num; count++) {
		if (count == 1) {
			answ = padd(*(polynominal + (count - 1)), *(polynominal + count));
		}
		else {
			answ = padd(answ, *(polynominal + count));
		}
	}
	//=========================PRINT=================//
	printf("Answer = ");
	printList(answ);


	//=========================FREE=================//

	for (int i = 0; i < num; i++)
		while (*(polynominal + i)) {
			delete((polynominal + i), NULL, NULL);
		}
	free(polynominal);


	return 0;

}

polyPointer insert(polyPointer poly)
{
	polyPointer rear, temp;
	MALLOC(rear, sizeof(*rear));
	poly = rear;
	int size, coef, expon, count = 0;
	printf("Input size of polynoimal %d :", count + 1);
	scanf("%d", &size);
	
	while (count < size) {
		printf("current : term %d\n coef : ", count + 1);
		scanf("%d", &coef);
		printf("expon : ");
		scanf("%d", &expon);
		attach(coef, expon, &rear);
		count++;
		printf("term %d entered successfully : %dx^%d\n==========================\n", count, coef, expon);
	}
	rear->link = NULL;
	temp = poly;
	poly = poly->link;
	free(temp);
	
	return poly;
}


polyPointer padd(polyPointer poly1, polyPointer poly2) {
	polyPointer answ, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	answ = rear;
	while (poly1 && poly2) {
		switch (COMPARE(poly1->expon, poly2->expon)) {
		case -1 :
			attach(poly2->coef, poly2->expon, &rear);
			poly2 = poly2->link;
			break;
		case 0:
			sum = poly1->coef + poly2->coef;
			if(sum)
				attach(sum, poly1->expon, &rear);
			poly1 = poly1->link;
			poly2 = poly2->link;
			break;
		case 1:
			attach(poly1->coef, poly1->expon, &rear);
			poly1 = poly1->link;
			break;
		}
	}

	for (; poly1; poly1 = poly1->link)
		attach(poly1->coef, poly1->expon, &rear);
	for (; poly2; poly2 = poly2->link)
		attach(poly2->coef, poly2->expon, &rear);
	rear->link = NULL;

	temp = answ;
	answ = answ->link;
	free(temp);

	return answ;
}

void attach(float coefficient, int exponenet, polyPointer* poly) {
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponenet;
	(*poly)->link = temp;
	*poly = temp;
}


void delete(polyPointer* poly, polyPointer trail, polyPointer x)
{
	if (trail)
		trail->link = x->link;
	else
		*poly = (*poly)->link;
	free(x);
}

void printList(polyPointer poly)
{
	for (; poly; poly = poly->link)
		if (!poly->link) {
			if (poly->expon == 0)
				printf("%d ", poly->coef);
			else
				printf("%dX^%d ", poly->coef, poly->expon);
		}
		else {
			if (poly->expon == 1)
				printf("%dX + ", poly->coef);
			else
				printf("%dX^%d + ", poly->coef, poly->expon);
		}
}

