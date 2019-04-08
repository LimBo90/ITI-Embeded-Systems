#include <stdio.h>
#include <stdint.h>

int add(int, int);
int sub(int, int);
int mul(int, int);

void main(){
    int (*ptr[3])(int,int) = {add, sub, mul};
    for(int i=0; i < 3; i++)
        printf("%d\n",ptr[i](5,7));
}

int add(int x, int y){
    return x+y;
}
int sub(int x, int y){
    return x-y;
}
int mul(int x, int y){
    return x*y;
}