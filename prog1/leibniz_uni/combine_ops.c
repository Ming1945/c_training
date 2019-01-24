/*
Compile: make combine_ops
Run: ./combine_ops
make combine_ops && ./combine_ops
*/

#include "base.h"

// Checks whether a and b are approximately equal.
bool approx(double a, double b) {
    return fabs(a - b) < 1e-6;
}

/*
Aufgabe 1a:
Implementieren Sie die Funktion arrays_equal, die genau dann wahr zurückgibt, wenn die Elemente der beiden übergebenen double-Arrays a und b paarweise ungefähr gleich sind. Beide Arrays haben die Länge n. Verwenden Sie zum Prüfen der ungefähren Gleichheit der Elemente die Funktion approx.
*/
bool arrays_equal(/*IN*/ const double* a, /*IN*/ const double* b, int n) {
    int counta = 0;
    int countb = 0;
    for(int j = 0; j < sizeof(a); j++){
        counta++;
    }
    for(int k = 0; k < sizeof(b); k++){
        countb++;
    }

    if(counta == countb) {
        for(int i = 0; i < n; i++){
            if(!approx(a[i], b[i])){
                return false;
            }
        }
    }
    return true;
}

void arrays_equal_test(void) {
    double a1[] = { 1.5, 2.3, 42.42 };
    double b1[] = { 1.5, 2.3, 42.42 };
    test_equal_b(arrays_equal(a1, b1, 3), true);
    // add more tests...
    double a2[] = { 1.2, 2.2, 3.7, 55.12 };
    double b2[] = { 1.2, 2.5, 3.7, 54.30 };
    test_equal_b(arrays_equal(a2, b2, 4), false);

    double a3[] = { 3.49999999, 5.0000000099, 14.55555559, 31.33333339 };
    double b3[] = { 3.49999998, 5.00000001, 14.5555556, 31.3333334};
    test_equal_b(arrays_equal(a3, b3, 4), true);
}

/*
Aufgabe 1b:
Implementieren Sie die Funktion array_copy, die eine dynamisch allokierte Kopie des Arrays a erstellt. Array a hat n Elemente. Verwenden Sie xcalloc zum reservieren des benötigten Speichers.
*/
double* array_copy(/*IN*/ const double* a, int n) {
    double * aCopy = xcalloc(n, sizeof(double));
    for(int i = 0; i < n; i++) {
        aCopy[i] = a[i];
    }

    return aCopy;
}

void array_copy_test(void) {
    double a1[] = { 1.5, 2.3, 42.42 };
    double* b1 = array_copy(a1, 3);
    test_equal_b(arrays_equal(a1, b1, 3), true);
    // add more tests...
    double a2[] = { 2.7, 44.5, 32.10, 55.55 };
    double* b2 = array_copy(a2, 4);
    test_equal_b(arrays_equal(a2, b2, 4), true);

    double aye[] = { 1.5, 2.3, 42.42, 1.3, 3.25 };
    double* uye = array_copy(aye, 5);
    test_equal_b(arrays_equal(aye, uye, 5), true);

    free(b1);
    free(b2);
    free(uye);
}

/*
Aufgabe 1c:
Implementieren Sie die Funktion shuffle, die die Elemente eines double-Arrays a mit n Elementen zufällig durcheinanderwürfelt. Das Eingabearray a wird dabei verändert. Jede mögliche Permutation soll die gleiche Auftretenswahrscheinlichkeit haben. Implementieren Sie dazu folgenden Algorithmus:
- vertausche das letzte Element (Index n-1) mit einem zufällig gewählten Element aus Indexintervall [0,n-1]
- vertausche das vorletzte Element (Index n-2) mit einem zufällig gewählten Element aus Indexintervall [0,n-2]
- vertausche das Element an Index n-3 mit einem zufällig gewählten Element aus Indexintervall [0,n-3]
- usw.
- vertausche das Element an Index 1 mit einem zufällig gewählten Element aus Indexintervall [0, 1]
Hinweis: Die Funktion i_rnd(int i) liefert eine zufällige ganze Zahl aus dem Intervall [0,i[ (0 ist inklusiv, i ist exklusiv), wobei jede ganze Zahl aus dem Intervall gleich wahrscheinlich ist.
*/
void shuffle(/*INOUT*/ double* a, int n) {
    // ...
    int rand1 = i_rnd(n);
    int rand2 = i_rnd(n-1);
    int rand3 = i_rnd(n-2);

    for(int i = 0; i < n; i++){
        if (i == n - 1) {
            int tmp = a[i];
            a[i] = a[rand1];
            a[rand1] = tmp; 
        }
        if (i == n - 2) {
            int tmp = a[i];
            a[i] = a[rand2];
            a[rand2] = tmp;
        }
        if (i == n - 3) {
            int tmp = a[i];
            a[i] = a[rand3];
            a[rand3] = tmp;
        }
        if ( i == 1) {
            int tmp = a[i];
            a[i] = a[0];
            a[0] = tmp;
        }
    }
}

void shuffle_test(void) {
    double a[] = { 1, 2, 3, 4 };
    printdaln(a, 4);
    for (int i = 0; i < 10; i++) {
        shuffle(a, 4);
        printdaln(a, 4);
    }
}

const char ops[] = { '+', '-', '*', '/' };
const int n_ops = sizeof(ops) / sizeof(char);

/*
Aufgabe 1d:
Implementieren Sie die Funktion random_ops, die das Array a der Länge n mit zufälligen Operatoren der Grundrechenarten füllt. Jeder Operator darf beliebig oft vorkommen.
Hinweis: Die Funktion i_rnd(int i) liefert eine zufällige ganze Zahl aus dem Intervall [0,i[ (0 ist inklusiv, i ist exklusiv), wobei jede ganze Zahl aus dem Intervall gleich wahrscheinlich ist.
*/
void random_ops(/*INOUT*/ char* a, int n) {
    for (int i = 0; i < n; i++) {
        int randops = i_rnd(4); //randops muss in der For-Schleife bleiben , damit es immer zufälliger OPs erstellen kann
        a[i] = ops[randops];
    }
}

void random_ops_test(void) {
    char o[3];
    for (int i = 0; i < 10; i++) {
        random_ops(o, 3);
        printcaln(o, 3);
    }
}

// Refers to a double array and counts how often this array has occurred yet.
typedef struct {
    double* array;
    int counter;
} ArrayCount;

// Computes the factorial of n: n!.
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

/*
Aufgabe 2b:
Implementieren Sie die Funktion update_array_counts, die für das Array a der Länge n die Zählerstände in array_counts der Länge m erhöht. Falls die Permutation a noch nicht vorhanden ist, muss ein noch nicht genutzter Eintrag in array_counts gesetzt werden. Es gilt m = n! (n Fakultät), da es für n Elemente n! Anordnungen gibt.
Hinweis: Speichern Sie in array_counts eine Kopie von a.
*/
void update_array_counts(/*INOUT*/ ArrayCount* array_counts, int m, /*IN*/ const double* a, int n) {
    // ...
    for (int i = 0 ; i < m ; i++) {
        if(array_counts[i].array == NULL){
            array_counts[i].array = array_copy(a, n);
            array_counts[i].counter++;
            break;
        }
        if (arrays_equal(a,array_counts[i].array, n)){
            array_counts[i].counter++;
            break;
        }
    }
}

// Gibt die Häufigkeit der verschiedenen Permutationen eines Arrays der Länge n aus.
void shuffle_frequency(int n) {
    double a[n];
    for (int i = 0; i < n; i++) {
        a[i] = i; // 0, 1, 2, ..., n - 1
    }
    int m = factorial(n);
    // Aufgabe 2a: Stellen Sie den Aufbau des Arrays array_counts grafisch dar.
    ArrayCount* array_counts = xcalloc(m, sizeof(ArrayCount));
    for (int i = 0; i < 1000 * m; i++) {
        shuffle(a, n);
        update_array_counts(array_counts, m, a, n);
    }
    for (int i = 0; i < m; i++) {
        printf("%4d%8d    ", i, array_counts[i].counter);
        printdaln(array_counts[i].array, n);
    }
    free(array_counts);
    // would have to free dynamically allocated contents of array_counts as well...
}

/*
Aufgabe 2d:
Implementieren Sie die Funktion evaluate, die n Zahlen und n-1 Operatoren übergeben bekommt und folgenden Postfix-Ausdruck auswertet:
numbers[0] numbers[1] ops[0] numbers[2] ops[1] numbers[3] ops[2] ... numbers[n-1] ops[n-2]
*/
double evaluate(/*IN*/ const double* numbers, /*IN*/ const char* ops, int n) {
    double a = numbers[0];
    int j = 0;

    for (int i = 1 ; i < n ; i++) {
        switch(ops[j]){
            case '+':
            a = a + numbers[i];//always goes to first index
            break;
            case '-':
            a = a - numbers[i];
            break;
            case '*':
            a = a * numbers[i];
            break;
            case '/':
            a = a / numbers[i];
            break;
        }
        j++;
    }
    return a;
}

/*
Aufgabe 2e:
Implementieren Sie die Funktion print_solution, die ein Array mit n double-Werten und ein gewünschtes Resultat übergeben bekommt. Die Funktion soll durch zufälliges Vertauschen der Anordnung der Zahlen und durch zufällige Wahl der Operatoren +, -, *, / eine solche Anordnung der Zahlen und Wahl der Operatoren finden, dass die Auswertung (approx.) den Wert result ergibt, sofern das möglich ist. Geben Sie auch aus, wie viele Durchläufe benötigt wurden, um eine Lösung zu finden. Nutzen Sie die Funktionen, die Sie in den vorherigen Teilaufgaben implementiert haben.
*/
void print_solution(/*IN*/ const double* numbers, int n, double result) {
    // ...
    int counter = 0;
    char o[n - 1];
    random_ops(o, n - 1);
    double* copy = array_copy(numbers, n);
    double f = result - 1;
    while(f != result){
        random_ops(o, n - 1);
        shuffle(copy, n);
        //printf("works until part 4 \n"); to check if the function entered the loop
        f = evaluate(copy,o,n);
        //printf("works until part 5,result =%f \n",f); same
        counter++;
    }
    printf("\nAnzahl Versuche= %d\n", counter);
}

int main(void) {
    arrays_equal_test();
    array_copy_test();
    shuffle_test();
    random_ops_test();
    
    shuffle_frequency(4);
    
    double a[] = { 2, 3, 7, 8 };
    print_solution(a, 4, 43); // 42 does not work, 43 does work
    
    /*double test[] = { 4, 3 , 2 , 1 };
    char testops[] = {'+' , '+' , '+' };*/
    
    //printf("this is shit %f\n", evaluate(test,testops,4));
    return 0;
}
