#include <stdio.h>

void main(){
    int const x = 5;
    /*const*/ int  *   ptr = &x;    //if you declare ptr to be a pointer to constant int then you can't modify *ptr
    *ptr = 10;
    printf("%d", x);
}                                  