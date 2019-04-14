#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint32_t real;
    uint32_t imaginary;
}Complex;

Complex add(Complex, Complex);

void main(){
    Complex x = {5,3};
    Complex y = {6,-4};
    Complex res = add(x,y);
    printf("%d%+di",res.real, res.imaginary);
}

Complex add(Complex n1, Complex n2){
    Complex res;
    res.real = n1.real + n2.real;
    res.imaginary = n1.imaginary + n2.imaginary;
    return res;
}