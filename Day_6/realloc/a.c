#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void printArray(uint16_t* ptr, uint8_t size);

void main(){
    uint8_t size = 5;
    uint16_t * ptr = (uint16_t *) calloc(size, sizeof(uint16_t));

    for(int i = 0; i < size; i++)
        ptr[i] = i;
    printArray(ptr, size);

    realloc(ptr, size*2);

    for(int i = size-1; i < 2*size; i++)
        ptr[i] = i;
    printArray(ptr, 2*size);
    
}

void printArray(uint16_t* ptr, uint8_t size){
    for(int i = 0; i < size; i++)
        printf("%d", ptr[i]);
    printf("\n");
}

