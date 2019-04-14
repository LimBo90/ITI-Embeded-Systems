#include "../include/Patient.h"


void printPatient(Patient * p){
    printf("Patient ID: %d\n", p->ID);
    printf("Patient name: %s\n", p->name);
    printf("Patient age: %d\n", p->age);
    printf("Patient name: %s\n", p->gender == MALE? "Male": "Female");
}


Patient * createPatient(uint32_t ID, char * name, uint32_t age, Gender gender){
    Patient* newPatient = (Patient*) malloc(sizeof(Patient));
    newPatient->ID = ID;
    newPatient->name = name;
    newPatient->age = age;
    newPatient->gender = gender;
    return newPatient;
}

void freePatient(Patient * p){
    free(p->name);
    free(p);
}