#include <stdio.h>
#include <stdlib.h>

int Random_number (void) {
    int c, n;
    printf("Ten random numbers in [0,100]\n");
    for (c = 1; c <= 10; c++) {
        n = rand() % 100;
        printf("%d\n", n);
    }
    return n;
}        

int main(void) {
    Random_number();
    return 0;
}