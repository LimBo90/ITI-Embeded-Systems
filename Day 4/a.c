#include <stdio.h>



void main(){
    int arr[3][3] = {1,2,3,4,5,6,7,8,9};
    int (*ptr)[3];
    ptr = arr;
    printf("%d", *(*(ptr + 0) + 0));
} 
