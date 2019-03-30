#include "base.h"

typedef struct DoubleNode {
    double value;
    struct DoubleNode* next;
} DoubleNode;

typedef struct DoubleList {
    DoubleNode* first;
    DoubleNode* last;
} DoubleList;

DoubleList* new_list(void) {
    return xcalloc(1, sizeof(DoubleList));
}

DoubleNode* new_node(double value) {
    DoubleNode* node = xcalloc(1, sizeof(DoubleNode));
    node->value = value;
    return node;
}

void print(DoubleList* list) {
    printf("[");
    for (DoubleNode* node = list->first; node != NULL; node = node->next) {
        printf("%f ", node->value);
    }
    printf("]\n");
}

void append(DoubleList* list, double value) {
    DoubleNode* p = new_node(value);
    if (list->last != NULL) list->last->next = p;
    list->last = p;
    if (list->first == NULL) list->first = p;
}

void free_list(DoubleList* list) {
    DoubleNode* next = NULL;
    for (DoubleNode* node = list->first; node != NULL; node = next) {
        next = node->next;
        free(node);
    }
    list->first = NULL;
    list->last = NULL;
    free(list);
}

DoubleList* list_of_string(char* s) {
    DoubleList* list = new_list();
    char* t = s;
    char* endp;
    while (*t != '\0') {
        if (isdigit(*t)) {
            if (t > s &&* (t - 1) == '.') t--; // check for '.'
            if (t > s &&* (t - 1) == '-') t--; // check for '-'
            append(list, strtod(t, &endp)); // convert digit string to int
            t = endp;
        } else {
            // assert: *t is not a digit, *t is not '\0'
            t++; // not a digit, skip
        }
    }
    return list;
}

//==========================================================================================================================================

//Return the mean of all values in the list
double mean(DoubleList* list) {
    int counter = 0 ;
    double totalValue = 0;
    double result = 0;
    if(list->first != NULL){ //ini harus di cek apakah node pertama dalam list ada apa ngga. jadi bukan cuma dicek llstnya NULL atau ngga.
    //sowieso list ga mungkin NULL. cuma node yang bisa NULL. list tetep selalu ada even isinya kosong ga ada nodes sama sekali
        for (DoubleNode* node = list->first ; node != NULL ; node = node->next){
            totalValue += node->value;
            counter++;
        }
    return result = totalValue / counter;
    }
    return 0;
}

double center_or_zero(DoubleList* list) {
    int counter = 0;
    for(DoubleNode* node = list->first ; node != NULL ; node = node->next) {
        counter++;
    }
    if (counter % 2 == 0) return 0;
    int mid = counter / 2;
    int new_counter = 0;
    if(list->first!= NULL){
        for(DoubleNode* node = list->first ; node != NULL ; node = node->next) {
            if(mid == new_counter) return node->value;
            new_counter++;
        }
    }
    return 0;
}

double max_min_difference(DoubleList* list) {
    if(list->first != NULL) { //jangan pernah bikin variabel diluar bedingung!
    double max = list->first->value;
    double min = list->first->value;
        for(DoubleNode* node = list->first ; node != NULL ; node = node->next) {
            if (node->value > max) max = node->value;
            if (node->value < min) min = node->value;
        }
        return max-min;
    }
    return 0;
    
}

void mean_test(void) {
    DoubleList* list = list_of_string("");
    test_within_d(mean(list), 0, 0.001);
	free_list(list);
    
    list = list_of_string("11");
    test_within_d(mean(list), 11, 0.001);
    free_list(list);
    
    list = list_of_string("1, -2");
    test_within_d(mean(list), -0.5, 0.001);
    free_list(list);
    
    list = list_of_string("-1, 2, -3, 4");
    test_within_d(mean(list), 0.5, 0.001);
    free_list(list);
    
}

void center_or_zero_test(void) {
    DoubleList* list = list_of_string("");
    test_equal_i(center_or_zero(list), 0);
	free_list(list);
    
    list = list_of_string("1.1");
    test_equal_i(center_or_zero(list), 1.1);
    free_list(list);
    
    list = list_of_string("-1, 2, -3, 4");
    test_equal_i(center_or_zero(list), 0);
    free_list(list);
    
    list = list_of_string("-1, 2, -3, 4, 5");
    test_equal_i(center_or_zero(list), -3);
    free_list(list);
    
}

void max_min_difference_test(void) {
    DoubleList* list = list_of_string("");
    test_within_d(max_min_difference(list), 0, 0.001);
	free_list(list);
    
    list = list_of_string("11");
    test_within_d(max_min_difference(list), 0, 0.001);
    free_list(list);
    
    list = list_of_string("1, -2");
    test_within_d(max_min_difference(list), 3.0, 0.001);
    free_list(list);
    
    list = list_of_string("-1, 2, -3, 4");
    test_within_d(max_min_difference(list), 7.0, 0.001);
    free_list(list);
    
}


//==========================================================================================================================================

int main(void) {
	base_init();
    base_set_memory_check(true); //to check if there are any memory leaks
    printf("4 TESTS FOR MEAN : \n");
    mean_test(); //3
    printf("\n4 TESTS FOR MAXMIN : \n");
    max_min_difference_test(); //2
    printf("\n4 TESTS FOR MEDIAN : \n");
    center_or_zero_test(); //1
    return 0;
}