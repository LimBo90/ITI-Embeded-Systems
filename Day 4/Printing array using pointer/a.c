#include <stdio.h>

void main(){
	int arr[5] = {1,2,3,4,5};
	int * ptr = arr;

	for(int * ptr = arr; ptr-&arr[0] < 5; ptr++)
		printf("%d", *ptr);
	
}