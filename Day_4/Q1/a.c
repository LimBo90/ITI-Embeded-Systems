#include <stdio.h>
void printArr(int[], int);
void swap(int*i, int*j);

void main(){
    int x[5] = {1,2,3,4,5};
    int y[5] = {6,7,8,9,10};
    
    for(int i = 0 ; i < 5; i++)
        swap(&x[i],&y[4-i]);

    printArr(x,5);
    printArr(y,5);
} 

void printArr(int arr[], int size){
    for(int i =0; i < size; i++)
        printf("%d\n", arr[i]);
    printf("-----\n");
}

void swap(int* i, int* j){
    *i ^= *j;
    *j ^= *i;
    *i ^= *j;
}