#include <stdio.h>
#include<stdint.h>
#include <stdlib.h>


#define MAX_NAME_SIZE 50

typedef enum{
    MALE,FEMALE
}Gender;

typedef struct{
    uint8_t age;
    Gender gender;
    uint32_t ID;
    char * name;
}Patient;

Patient* getPatientFromUser();
Gender getGenderFromUser();
void printPatient(Patient);
Patient* createPatient(uint32_t, char*, uint8_t, Gender);

void main(){
    printPatient(*getPatientFromUser());
}


Patient* getPatientFromUser(){
    char * name = malloc(MAX_NAME_SIZE*sizeof(char));
    uint8_t age;
    uint32_t ID;
    Gender gender;
    printf("Enter patient's ID: ");
    scanf("%d", &ID);
    printf("Enter patient's name: ");
    scanf("%s",name);
    printf("Enter patient's age: ");
    scanf("%d", &age);
    gender = MALE;
    return createPatient(ID ,name, age, gender);
}

Gender getGenderFromUser(){
    Gender gender;
    printf("Enter patient's gender (M/F)?");
    while(1){ 
        char choice;
        scanf("%c", &gender);
        if(choice == 'm' || choice == 'M'){
            gender = MALE;
            break;
        }else if(choice == 'f' || choice == 'F'){
            gender = FEMALE;
            break;
        }else{
            printf("Please enter M for male or F for female: ");
        }
    }
    return gender;
}

void printPatient(Patient p){
    printf("Patient ID: %d\n", p.ID);
    printf("Patient name: %s\n", p.name);
    printf("Patient age: %d\n", p.age);
    printf("Patient name: %s\n", p.gender == MALE? "Male": "Female");
}


Patient * createPatient(uint32_t ID, char * name, uint8_t age, Gender gender){
    Patient* newPatient = (Patient*) malloc(sizeof(Patient));
    newPatient->ID = ID;
    newPatient->name = name;
    newPatient->age = age;
    newPatient->gender = gender;
}