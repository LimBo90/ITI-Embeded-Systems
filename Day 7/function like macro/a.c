#include <stdio.h>

#define ADD(a,b) (a+b)
// wrong function marco
#define PRINT() printf("Hello ");\
                printf("World\n");\
                printf("Abdullah\n");

// right function marco
#define PRINT2() do{\
                    printf("Hello ");\
                    printf("World\n");\
                    printf("Abdullah\n");\
                }while(0);

void main(){
    printf("%d\n", ADD(5,6));
    // this will print world abdullah although the condition of the if is false
    if(0)
        PRINT();

    //this will not execute PRINT2 as expected
    if(0)
        PRINT2();
}