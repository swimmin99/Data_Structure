//list3.c
//PROBLEM : Generate doubley linked list in order of input, free the list
//INPUT : .txt/int/ex) 1 3 5 7
//ADT : insert/delete/printorderlist/printreverselist
//=======================================================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#define MALLOC(p,s) if (! ( (p) = malloc (s) ) ) { fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}
typedef struct node* nodePointer;
typedef struct node {
    nodePointer llink;
    int data;
    nodePointer rlink;
};

nodePointer createNode();
void dinsert(nodePointer node, nodePointer newnode);
void delete(nodePointer node, nodePointer deleted);
void printorderlist(nodePointer node);
void printreverselist(nodePointer node);

int main() {
    nodePointer head = createNode();
    FILE* fp = NULL;
    if ((fp = fopen("in.txt", "r+")) == NULL) { puts("file open failure"); exit(EXIT_FAILURE); }

    int num;

    head->llink = head;
    head->rlink = head;
    
    while (!feof(fp)) {
        nodePointer temp = createNode();
        fscanf(fp, "%d", &temp->data);
        dinsert(head->llink, temp);
    }

    printorderlist(head);
    puts(" ");
    printreverselist(head);
    while (head->llink != head) {
        delete(head, head->llink);
    }
    free(head);
    head = NULL;
    fclose(fp);
    return 0;
}



nodePointer createNode() {
    nodePointer temp = NULL;
    MALLOC(temp, sizeof(*temp));
    return temp;
}

void dinsert(nodePointer node, nodePointer newnode) {
    newnode->llink = node;
    newnode->rlink = node->rlink;
    node->rlink->llink = newnode;
    node->rlink = newnode;
}

void delete(nodePointer node, nodePointer deleted) {
    deleted->llink->rlink = deleted->rlink;
    deleted->rlink->llink = deleted->llink;
    free(deleted);


}

void printorderlist(nodePointer node) {
    nodePointer temp = node;
    while (1) {
        temp = temp->rlink;
        printf("%d ", temp->data);
        if (temp->rlink == node)
            break;
    }
}

void printreverselist(nodePointer node) {
    nodePointer temp = node;
    while (1) {
        temp = temp->llink;
        printf("%d ", temp->data);
        if (temp->llink == node)
            break;
    }
}