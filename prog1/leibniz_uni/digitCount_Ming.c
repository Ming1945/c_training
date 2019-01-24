#include "base.h"

void digitCount (){
    int ndigit[10]; //wir erstellen ein Array "ndigit" mit der Länge 10
    int i = 0; 
    
    while(i < 10) {
        ndigit[i] = 0; 
        i++;
    }
    
    while ((i = getchar()) != EOF) {
        if (i >= '0' && i <= '9') {
            ndigit[i - '0']++;
        } 
    }
         
    i = 0;
    while (i < 10){
        printf("%4d : %d times \n" , i , ndigit[i]);
        i++;
    }
}

int main (void) {
    digitCount();
    return 0;
}