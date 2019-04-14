#include <stdio.h>

typedef struct {
    int * name;
    int age;
    int salary;
}Person;


void main(){
Person x = {{1,2,3}, 12, 22};
Person y = {{4,5,6}, 20,20};
printArr(x.name, 3);
printArr(y.name, 3);
y = x;
y.name[2] = 2000;
printArr(x.name, 3);
printArr(y.name, 3);



// printf("%s\n", x.name);
// x.name = "as";
// printf("%s\n", x.name);
// *(x.name+2)  = 'F';
}

void printArr(int * arr, int size){
    for(int i = 0 ; i < size; i++)
        printf("%d ", *arr[i]);
    printf("\n");
}