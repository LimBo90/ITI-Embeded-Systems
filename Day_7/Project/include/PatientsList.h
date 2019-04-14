#ifndef PATIENTLIST_H_
#define PATIENTLIST_H_

#include "../include/Patient.h"
#include "assert.h"
#include "stdint.h"

typedef  struct PATIENTLIST PatientList;

struct PATIENTLIST{
    Patient * patient;
    PatientList * next;
    PatientList * prev;
};

PatientList* addToList(PatientList*, Patient*);
Patient* getPatient(PatientList*, uint32_t );
uint8_t deletePatient(PatientList*, uint32_t );
void printList(PatientList*);

#endif