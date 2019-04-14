#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "include/Patient.h"
#include "include/PatientsList.h"

#define NO_OF_RESERVATIONS 5
#define ADMIN_PASS "1234"
#define NO_OF_PASSWORD_TRIES 3
#define MAX_PASS_SIZE 10

void menu(uint16_t);
uint16_t login();
void viewPatient();
void addPatient();
void editPatient();
Gender getGenderFromUser();
void addReservation();
void cancelReservation();
void printReservations(int8_t);
Patient * getPatientFromUser();
char* getString();
uint32_t getNumber();

Patient * reservations[NO_OF_RESERVATIONS] = {NULL,NULL,NULL,NULL,NULL};
PatientList * patientLists = NULL;
uint16_t mode;

int main(){
    while(1){
        uint16_t mode = login();
        if(!mode)
            break;
        menu(mode);
    }
    printf("Exiting... \n");
    system("pause");
    return 0;
}

void menu(uint16_t mode){
    printf("========== Main Menu ===========\n");
    switch(mode){
        case 1:
        while(1){
            printf("1. View patient\n");
            printf("2. View Reservations \n");
            printf("0. Quit");
            printf(": ");
            uint32_t choice = getNumber();
            while(!(choice >=0 && choice <= 2)){
                printf("Please enter a valid option [0:4]\n: ");
                choice = getNumber();
            }
            switch(choice){
                case 1: viewPatient();   break;
                case 2: printReservations(1); system("pause");  break;
                case 0: return ;
            }
        }
        case 2:
        while(1){
            
            printf("1. View Patients\n");
            printf("2. Add new patient \n");
            printf("3. Edit patient \n");
            printf("4. View Reservations \n");
            printf("5. Reserve a slot\n");
            printf("6. Cancel reservation\n");
            printf("0. Quit");
            printf(": ");
            uint32_t choice = getNumber();
            while(!(choice >=0 && choice <= 6)){
                printf("Please enter a valid option [0:4]\n: ");
                choice = getNumber();
            }
            switch(choice){
                case 1: printList(patientLists); system("pause"); break;
                case 2: addPatient();   break;
                case 3: editPatient();  break;
                case 4: printReservations(1); system("pause"); break;
                case 5: addReservation();   break;
                case 6: cancelReservation(); break;
                case 0: return ;
            }
        }
    }
}

uint16_t login(){
    printf("============ Login =============\n");
    printf("1. User Mode\n");
    printf("2. Admin Mode\n");
    printf("0. Quit\n");
    printf(": ");
    char * str ;
    int16_t choice = getNumber();
    while(!(choice >= 0 || choice <= 2)){
        printf("Please enter a valid option [0:2]\n: ");
        choice = getNumber();
    }
    switch(choice){
        case 2:
        for(int i = NO_OF_PASSWORD_TRIES; i>0; i--){    
            printf("Enter password (max length 10) [%d tries left]: ", i);
            
            char * str = getString(MAX_PASS_SIZE);
            if(strncmp(str, ADMIN_PASS,10) == 0)
                return 2;
        }
        printf("You have run out of tries.\n");
        return 0;

        case 1:
            return 1;

        case 0:
            return 0;
        
    }

}

void viewPatient(){
    Patient * p = getPatientFromUser();
    if (p == NULL)
        return;
    printPatient(p);
    system("pause");
}

void addPatient(){
    uint32_t age;
    uint32_t ID;
    Gender gender;
    char * name;
    printf("============ Add Patient =============\n");
    printf("Enter patient's ID: ");
    ID = getNumber();
    if(getPatient(patientLists, ID) != NULL){
        printf("ID already exists\n");
        return;
    }
    printf("Enter patient's name: ");
	name = getString(MAX_NAME_SIZE);
    printf("Enter patient's age: ");
    age = getNumber();
    gender = getGenderFromUser();
    if(patientLists)
        addToList(patientLists, createPatient(ID , name, age, gender));
    else
        patientLists = addToList(patientLists, createPatient(ID , name, age, gender));
    return;
}

void editPatient(){
    printf("============ Edit Patient ============\n");
    Patient * p = getPatientFromUser();
    if(p == NULL)
        return;
    printPatient(p);
    printf("1. Edit patient's ID: \n");
    printf("2. Edit patient's name \n");
    printf("3. Edit paient's age\n");
    printf("4. Edit patient's gender\n");
    printf(": ");
    uint16_t c = getNumber();
    char * temp = p->name;
    while(!(c >= 1 && c <= 4)){
        printf("Please enter a valid option [1:4]\n: ");
        printf(": ");
        c = getNumber();
    }
    switch(c){
        case 1:
            printf("Enter patient's ID: ");
            p->ID = getNumber();
            break;
        case 2:
            printf("Enter patient's name: ");
            p->name = getString(MAX_NAME_SIZE);
            break;
        case 3:
            printf("Enter patient's age: ");
            p->age = getNumber();
            break;
        case 4:
            p->gender = getGenderFromUser();
            break;
    }
    return;    
}


Gender getGenderFromUser(){
    Gender gender;
    printf("Enter patient's gender (M/F): ");
    while(1){ 
        char choice;
        scanf("%c", &choice);
        getchar();
        if(choice == 'm' || choice == 'M'){
            gender = MALE;
            break;
        }else if(choice == 'f' || choice == 'F'){
            gender = FEMALE;
            break;
        }else{
            printf("Please enter a valid option (M/F)\n: ");
        }
    }
    return gender;
}

void addReservation(){
    printf("============ Reserve A Slot ============\n");
    printReservations(0);
    printf("Enter the slot you want to reserve: ");
    uint16_t choice = getNumber();
    while(!(choice >= 1 && choice <= 5)){
        printf("Please enter a valid slot [1:5]\n: ");
        choice = getNumber();
    }
    
    if(reservations[choice-1] != NULL){
        printf("Slot already reserved\n");
        return;
    }
    Patient * patient = getPatientFromUser();
    if(patient != NULL)
        reservations[choice-1] = patient;
    return;
}

void cancelReservation(){
    printf("========== Cancel Reservation ==========\n");
    printReservations(1);
    printf("Enter the slot you want to cancel: ");
    uint16_t choice = getNumber();
    while(!(choice >= 1 && choice <= 5)){
        printf("Please enter a valid slot [1:5]\n: ");
        uint8_t choice = getNumber();
    }
    reservations[choice-1] = NULL;
}

void printReservations(int8_t includeReserved){
    if(includeReserved)
        printf("============ Reservations ============\n");
    else
        printf("======= Free Reservation Slots =======\n");
    for (int i = 0; i < NO_OF_RESERVATIONS; i++){
        int a  = 2 + i/2;
        int b = 2 + (i+1)/2;
        int c = 3 - (3*(i%2));
        int d = 3 - c;
        if(reservations[i]){
            if(!includeReserved)
                continue;
            printf("%d| 0%d:%d0 PM to 0%d:%d0 PM | ", i+1, a, d, b, c);
            printf("Resserved for patient [%d]\n", reservations[i]->ID);
        }else{
            printf("%d| 0%d:%d0 PM to 0%d:%d0 PM | ",i+1, a, d, b, c);
            printf("FREE\n");
        }
    }
}

Patient * getPatientFromUser(){
    printf("Enter the ID of the patient: ");
    uint32_t ID = getNumber();
    Patient * patient = getPatient(patientLists, ID);
    if(patient == NULL)
        printf("No patient with that ID\n");
    return patient;
}

char* getString(uint32_t maxSize){
    char * str = malloc(maxSize*sizeof(char));
   scanf("%[^\n]%*c", str); 
    return str;
}

uint32_t getNumber(){
    uint32_t res;
    scanf("%d", &res);
    getchar();
    return res;
}