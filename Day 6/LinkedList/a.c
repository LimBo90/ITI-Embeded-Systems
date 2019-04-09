#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct node{
    int data;
    struct node* next;
}Node;

Node * createNode(int);
void printLinkedList(Node *);
void deleteLastNode(Node * );
Node * getNode(Node * , int );
void deleteNode(Node * head, int a);
void insertNode(Node* head, int a, int data);
Node * getNodeFromLast(Node * head, int a);

void main(){
    int size;
    Node* head = (Node*)malloc(sizeof(Node));
    printf("Enter the size: ");
    scanf("%d", &size);
    Node * tail;

    for(int i = 0; i < size; i++){
        int data;
        scanf("%d", &data);
        if(i == 0){
            head = createNode(data);
            head->next = NULL;
            tail = head;
        }else{
            Node * n = createNode(data);
            tail->next = n;
            tail = n;
        }
    }

    printLinkedList(head);
    printf("===========\ndeleteLastNode \n");
    deleteLastNode(head);
    printLinkedList(head);
    printf("===========\ngetNode(3) = %d\n", getNode(head,3)->data);
    printf("===========\ndeleteNode(3)\n");
    deleteNode(head, 3);
    printLinkedList(head);   
    printf("===========\ninsertNode(2, 17)\n");
    insertNode(head, 2, 17);
    printLinkedList(head);
    printf("===========\ngetNodeFromLast(5) = %d\n", getNodeFromLast(head,5)->data);
}

Node* createNode(int data){
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void printLinkedList(Node * head){
    Node * n = head;
    while(1){
        printf("%d ", n->data);
        if(n->next == NULL)
            break;
        n = n->next;
    }
    printf("\n");
}


void deleteLastNode(Node * head){
    Node * n = head;
    while(n->next->next != NULL)
        n = n->next;
    free(n->next);
    n->next = NULL;
}

Node * getNode(Node * head, int a){
    Node * n = head;
    for(int i = 0; i < a; i++)
        n = n->next;
    return n;
}

void deleteNode(Node * head, int a){
    Node * n = head;
    for(int i = 0; i < a-1; i++)
        n = n->next;
    Node* removedNode = n->next;
    n->next = n->next->next;
    free(removedNode);
}

void insertNode(Node* head, int a, int data){
    Node * n = head;
    for(int i = 0; i < a; i++)
        n = n->next;
    Node * newNode = createNode(data);
    newNode->next= n->next;
    n->next = newNode;
}

Node * getNodeFromLast(Node * head, int a){
    int size = 0;
    Node * n = head;
    while(n->next != NULL){
        // printf("%d \n", n->data);
        n = n->next;
        size++;
    }
    size++;
    return getNode(head, size-a-1); 
}