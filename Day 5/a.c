#include <stdio.h>

struct number{
    int n;
    int repeatations;
};

struct number getMostRepeated(int arr[], int size);

void main(){
    int arr[9] = {1,2,2,0,5,0,0,0,9};
    struct number mostRepeated = getMostRepeated(arr, 9);
    printf("n = %d\nno of repeatations = %d", mostRepeated.n, mostRepeated.repeatations);
}


struct number getMostRepeated(int arr[], int size){
    int count[10]={0};
    struct number res;
    res.repeatations = 0;
    for (int i = 0; i < size; i++)
        count[arr[i]]++;
    
    for (int i = 0; i < size; i++)
        if(count[i] > res.repeatations){
            res.repeatations = count[i];
            res.n = i;
        }
    return res;
}