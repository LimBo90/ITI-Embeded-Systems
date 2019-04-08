#include <stdio.h>
#include <stdint.h>

int add(int, int);

void main(){
    int(*ptr)(int,int);
    ptr = add;
    printf("%d", ptr(5,7));
}

int add(int x, int y){
    return x+y;
}