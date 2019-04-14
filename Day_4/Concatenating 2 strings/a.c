#include <stdio.h>

void concatenate(char*, char*, char*);

void main(){
    char* name1 = "Abdullah";
    char* name2 = "Abdelrazik";
    char res[50];
    concatenate(name1,name2, res);

    printf("%s\n", res);
} 

void concatenate(char* s1, char* s2, char* res){
    int i = 0, j = 0;
        int flag = 1;

        while(1){
            char c = flag? s1[j] : s2[j]; 
            if(c == '\0' && flag){
                flag = 0;
                j=0;
                c = s2[j];
            }
            res[i] = c;
            if(c == '\0'  && !(flag))
                break;
            i++;
            j++;
        }
}