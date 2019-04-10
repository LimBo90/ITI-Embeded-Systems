#include <stdio.h>
#include <stdint.h>
#include "a.h"

void printBinary(uint8_t n){
    for (int i = 0; i < 8; i++) {
        printf("%d", !!((n << i) & 0x80));
    }
    printf("\n");
}

void main(){
    uint8_t x = 211;
    printf("Number: ");
    printBinary(x);
    printf("SET_BIT 3: ");
    printBinary(SET_BIT(x,3));
    printf("CLR_BIT 6: ");
    printBinary(CLR_BIT(x,6));
    printf("TOGGLE_BIT 3: ");
    printBinary(TOGGLE_BIT(x,3));
    printf("TOGGLE_BIT 1: ");
    printBinary(TOGGLE_BIT(x,1));
}

