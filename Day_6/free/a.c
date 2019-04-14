#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void printArray(uint16_t* ptr, uint8_t size);

void main(){
    uint8_t size = 5;
    uint16_t * ptr = (uint16_t *) calloc(size, sizeof(uint16_t));
    printf("ptr = %p\n", ptr);

    for(int i = 0; i < size; i++)
        ptr[i] = i;
    printArray(ptr, size);

    uint16_t * ptr1 = ptr;
    printf("ptr = %p\n", ptr);
    printf("ptr1 = %p\n", ptr1);
    printArray(ptr1, size);
    free(ptr);
    printf("ptr = %p\n", ptr);
    printf("ptr1 = %p\n", ptr1);
    printArray(ptr1, size);
}

void printArray(uint16_t* ptr, uint8_t size){
    for(int i = 0; i < size; i++)
        printf("%d\n", ptr[i]);
    printf("\n");
}

