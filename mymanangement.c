#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void read();
int input();

int view();
void viewAll();
void viewName();
void viewDepartment();
int edit();
void editName(int j);
void viewAddress();
int delete();
void deleteName(int j);

struct S {
	char name[20];
	char dept[20];
	char telno[15];
	int age;
	char addr[100];
};

int cntTot = 0;

struct S data[300];
FILE* fp;

int main()
{
	while (1)
	{
		menu();
	}

	return 0;

}

void menu()
{

	int i = 0;

	do {

		system("cls");
		printf("\n\n\n\t1) 회원정보 등록\n");
		printf("\t2) 회원정보 조회\n");
		printf("\t3) 회원정보 수정\n");
		printf("\t4) 회원정보 삭제\n");
		printf("\t5) 종료\n");

		printf("\n\n\t메뉴를 입력하세요 : ");
		scanf("%d", &i);

	} while (i < 1 || i > 5);

	switch (i) {

	case 1:
		while (input()) {}
		break;
	case 2:
		while (view()) {}
		break;
	case 3:
		while (edit()) {}
		break;
	case 4:
		while (delete()) {}
		break;
	case 5:
		exit(0);
	}

	return;
}



int input() {

	struct S data;
	fp = fopen("info.txt", "a+");

	if (fp == NULL) {
		printf("file open error. \n");
		exit(0);
	}


	printf("\n\n\n\t이름 (종료: end) : ");
	scanf("%s", data.name);

	if (!strcmp(data.name, "end"))
	{
		return 0;
	}


	printf("\t부서 : ");
	scanf("%*c%s", data.dept);

	printf("\t전화번호 : ");
	scanf("%*c%s", data.telno);

	printf("\t나이 : ");
	scanf("%*c%d", &data.age);

	printf("\t주소 : ");
	scanf("%*c%[^\n]", data.addr); // "%[^\n]" or "%[^\n]s" : new line 이전의 모든 문자.
	scanf("%*c");


	fprintf(fp, "%20s %20s %15s %5d %100s\n", data.name, data.dept, data.telno, data.age, data.addr);

	fclose(fp);

	printf("\n\n\t1 레코드 입력이 완료되었습니다. (엔터)");

	getc(stdin);

	return 1;

}


int view () {

	
	int input = 0;
	printf("\n\n\n\t1. 전부조회 2. 이름조회 3. 주소조회 4. 부서조회 5. 종료 : ");
	scanf("%d", &input);
	read();
	switch (input) {
	case 1: viewAll(); break;
	case 2: viewName(); break;
	case 3: viewAddress(); break;
	case 4: viewDepartment(); break;
	case 5: return 0;
	}

	return 1;
}


void viewName() {
	char queryName[20];
	printf("\n\n\n\t검색할 이름 입력 : ");
	scanf("%s", queryName);

	for (int i = 0; i < cntTot; i++) {
		if (!strcmp(data[i].name, queryName)) {
			printf("%s\n", data[i].name);
			printf("%s\n", data[i].dept);
			printf("%s\n", data[i].addr);
			printf("%s\n", data[i].telno);
			printf("%d\n", data[i].age);
		}
	}

	printf("완료되었습니다");
	getc(stdin);
	getc(stdin);

	return;

}

void viewAll() {
	for (int i = 0; i < cntTot; i++) {
		 {
			printf("%s\n", data[i].name);
			printf("%s\n", data[i].dept);
			printf("%s\n", data[i].addr);
			printf("%s\n", data[i].telno);
			printf("%d\n", data[i].age);
		}
	}

	printf("완료되었습니다");
	getc(stdin);
	getc(stdin);

	return;

}

void viewAddress() {
	char queryName[20];
	printf("\n\n\n\t검색할 주소 입력 : ");
	scanf("%s", queryName);

	for (int i = 0; i < cntTot; i++) {
		if (strstr(data[i].addr, queryName)) {
			printf("%s\n", data[i].name);
			printf("%s\n", data[i].dept);
			printf("%s\n", data[i].addr);
			printf("%s\n", data[i].telno);
			printf("%d\n", data[i].age);
		}
	}

	printf("완료되었습니다");
	getc(stdin);
	getc(stdin);

	return;


}

void viewDepartment() {
	char queryName[20];
	printf("\n\n\n\t검색할 부서 입력 : ");
	scanf("%s", queryName);

	for (int i = 0; i < cntTot; i++) {
		if (!(strcmp(data[i].dept, queryName))) {
			printf("%s\n", data[i].name);
			printf("%s\n", data[i].dept);
			printf("%s\n", data[i].addr);
			printf("%s\n", data[i].telno);
			printf("%d\n", data[i].age);
		}
	}

	printf("완료되었습니다");
	getc(stdin);
	getc(stdin);

	return;


}

void read()
{

	fp = fopen("info.txt", "r");

	if (fp == NULL) {
		printf("file open error. \n");
		exit(0);
	}

	cntTot = 0;
	int i = 0;
	while (fscanf(fp, "%20s %20s %15s %5d %[^\n]s",
		data[i].name, data[i].dept, data[i].telno, &data[i].age, data[i].addr) == 5) {

		++cntTot;
		++i;
	}

	fclose(fp);
}

int edit() {

	int choice = 0;
	char queryName[20];
	printf("\n\n\n\t수정할 회원이름을 입력하세요 (종료: end) : ");
	scanf("%s", queryName);

	if (!strcmp(queryName, "end"))
	{
		return 0;  // 종료 숫자
	}

	read();

	for (int j = 0; j < cntTot; ++j)
	{
		if (!strcmp(data[j].name, queryName))
		{

			printf("%3d", j + 1);
			printf("%20s, ", data[j].name);
			printf("%20s, ", data[j].dept);
			printf("%15s, ", data[j].telno);
			printf("%5d, ", data[j].age);
			printf("%100s\n\n", data[j].addr);

			printf("\n\n\t수정할 회원이 맞습니까? (1. 예,  2. 아니오. 3. 나가기) : ");
			scanf("%d", &choice);

			if (choice == 3)
			{
				return 0;
			}
			else if (choice == 1)
			{

				editName(j);

				return 1;
			}

			// break;
		}

	}

	printf("\n\n\t수정을 원하는 회원이 존재하지 않습니다. (엔터)");

	getc(stdin); getc(stdin);


	return 1;
}

void editName(int find)
{

	struct S oneRecord;

	fp = fopen("info.txt", "r+");
	if (fp == NULL) {
		printf("file open error. \n");
		exit(0);
	}




	printf("\n\n\n\t수정할 이름 (종료: end) : ");
	scanf("%20s", oneRecord.name);

	if (!strcmp(oneRecord.name, "end"))
	{
		return;
	}

	printf("\t수정할 부서 : ");
	scanf("%*c%20s", oneRecord.dept);

	printf("\t수정할 전화번호 : ");
	scanf("%*c%15s", oneRecord.telno);

	printf("\t수정할 나이 : ");
	scanf("%*c%5d", &oneRecord.age);


	printf("\t수정할 주소 : ");
	scanf("%*c%[^\n]", oneRecord.addr); // "%[^\n]" or "%[^\n]s" : new line 이전의 모든 문자.
	scanf("%*c");



	fseek(fp, find * sizeof(struct S) + (find * 6), SEEK_SET);   // 빈 칸, 개행문자 포함
	// fseek(fp, find * sizeof(struct S) + (find * 4) + (find * 2), SEEK_SET);    
	// fseek(fp, find * (sizeof(struct S) + 6), SEEK_SET);  

	fprintf(fp, "%20s %20s %15s %5d %100s", oneRecord.name, oneRecord.dept, oneRecord.telno, oneRecord.age, oneRecord.addr);
	printf("\n\n\t수정 완료되었습니다. (엔터)");

	fclose(fp);

	return;
}


int delete() {

	int choice = 0;
	char queryName[20];
	printf("\n\n\n\t삭제할 회원이름을 입력하세요 (종료: end) : ");
	scanf("%s", queryName);

	if (!strcmp(queryName, "end"))
	{
		return 0;
	}

	read();

	for (int j = 0; j < cntTot; ++j)
	{
		if (!strcmp(data[j].name, queryName))
		{

			printf("%3d", j + 1);
			printf("%20s, ", data[j].name);
			printf("%20s, ", data[j].dept);
			printf("%15s, ", data[j].telno);
			printf("%d, ", data[j].age);
			printf("%100s\n\n", data[j].addr);

			printf("\n\n\t삭제할 회원이 맞습니까? (1. 예,  2. 아니오. 3. 나가기) : ");
			scanf("%d", &choice);

			if (choice == 3)
			{
				return 0;
			}
			else if (choice == 1)
			{

				deleteName(j);

				return 1;
			}

			// break; 
		}

	}

	printf("\n\n\t삭제를 원하는 회원이 존재하지 않습니다. (엔터)");

	getc(stdin); getc(stdin);


	return 1;

}


void deleteName(int find)
{
	fp = fopen("info.txt", "w");

	for (int k = 0; k < cntTot; ++k)
	{
		if (k != find)
		{
			fprintf(fp, "%20s %20s %15s %5d %100s\n", data[k].name, data[k].dept, data[k].telno, data[k].age, data[k].addr);
		}
	}


	printf("\n\n\t삭제 완료되었습니다. (엔터)");

	fclose(fp);

	getc(stdin); getc(stdin);

	return;
}