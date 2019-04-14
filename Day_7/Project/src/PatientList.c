#include "../include/PatientsList.h"



PatientList * addToList(PatientList *head, Patient * p){
    if(getPatient(head, p->ID) != NULL)
        return NULL;
    PatientList* newNode = (PatientList*) malloc(sizeof(PatientList));
    newNode->patient = p;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (head == NULL){
       return newNode;
    }else{
        while(head->next != NULL)
            head = head->next;
        head->next = newNode;
        newNode->prev = head;
    }
    return newNode;
}

Patient * getPatient(PatientList* head, uint32_t ID){
    if(head == NULL)
        return NULL;
    while(head != NULL){
        if(head->patient->ID == ID)
            return head->patient;
        head = head->next;
    }
    return NULL;
}

uint8_t deletePatient(PatientList* head, uint32_t ID){
    while(head != NULL){
        if(head->patient->ID == ID ){
            if(head->prev != NULL)
                head->prev->next = head->next;
            if(head->next != NULL)
                head->next->prev = head->prev;
            freePatient(head->patient);
            free(head);
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void printList(PatientList * head){
    printf("============== Patients ==============\n");
    if(head == NULL)
        return;
    while(1){
        printPatient(head->patient);
        if(head->next == NULL)
            break;
        head = head->next;
        printf("--------------------------------------\n");
    }
}