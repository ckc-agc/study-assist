// This program will produce error and cannot be compiled.
#include <stdio.h>

void my_print(void){
    printf("Hello World\n");
}

int main(void){
    my_print(1);
    return 0;
}