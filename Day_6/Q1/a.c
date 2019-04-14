#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint16_t age;
    uint32_t ID;
    char  name[50];
}Student;

void printStudent(Student s);

void main(){
    uint16_t n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    Student * students = (Student*) malloc(n * sizeof(Student));


    for(int i = 0; i < n; i++){
        printf("Student %d\n", i);
        printf("ID: ");
        scanf("%d", &students[i].ID);
        printf("name: ");
        scanf("%s", students[i].name);
        printf("age: ");
        scanf("%d", &students[i].age);
    }

    for (int i = 0; i < n; i++){
        printf("%d============\n", i);
        printStudent(students[i]);
    }
}


void printStudent(Student s){
    printf("ID: %d name:%s age: %d\n", s.ID, s.name, s.age);
}