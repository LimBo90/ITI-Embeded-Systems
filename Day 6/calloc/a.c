#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void printArray(uint16_t* ptr, uint8_t size);
uint32_t sumArray(uint16_t* ptr, uint8_t size);

void main(){
    uint8_t size;
    printf("Enter the size of array: ");
    scanf("%d", &size);
    uint16_t * ptr = (uint16_t *) calloc(size, sizeof(uint16_t));

    for(int i = 0; i < size; i++){
        printf("Enter number %d: ", i);
        scanf("%d", &ptr[i]);
    }

    printArray(ptr, size);
    
    printf("Sum = %d", sumArray(ptr, size));
}

void printArray(uint16_t* ptr, uint8_t size){
    for(int i = 0; i < size; i++)
        printf("%d", ptr[i]);
    printf("\n");
}

uint32_t sumArray(uint16_t* ptr, uint8_t size){
    uint32_t sum = 0;
    for(int i = 0; i < size; i++)
        sum += ptr[i];
    return sum;
}

