#ifndef PATIENT_H_
#define PATIENT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 50

typedef enum{
    MALE,FEMALE
}Gender;

typedef struct{
    uint32_t age;
    uint32_t ID;
    Gender gender;
    char * name;
}Patient;

void printPatient(Patient* p);
Patient * createPatient(uint32_t ID, char * name, uint32_t age, Gender gender);
void freePatient();

#endif