/*
Compile: make integer_tree_test
Run: ./integer_tree_test
make integer_tree_test && ./integer_tree_test
*/

#include "integer_tree.h"

void get_odd_even_rec(BTNode* tree, Node** odd, Node** even){
	// (d) todo: implement
}

//Option type
typedef struct{
	bool valid;
	int value;
} Option_int; 

// Creates a new option int 
Option_int make_option_int(bool valid, int value){
	Option_int option_int;
	option_int.valid = valid;
	option_int.value = value;
	return option_int;
}

bool is_sorted(BTNode* node){
	// (f) todo: implement
	return false;
}


int main(void) {
    base_init();
    base_set_memory_check(true);

    int values[] = { 22, 44, 19, 8, 97, 36, 56, 33, 29 };
    int n = sizeof(values) / sizeof(int);
	
	printiln(n);
    
    // (a) todo: implement
    BTNode* t = NULL;
    // ...

    BTNode* t2 = new_btnode(0, new_btnode(1, new_btnode(11, NULL, NULL), new_btnode(12, NULL, NULL)), new_btnode(2, NULL, new_btnode(7, NULL, NULL)));
    println_tree(t2);
    free_tree(t2);
    
	// (c) todo: implement
    
    
    // (d) todo: implement
	Node* even = NULL;
	Node* odd = NULL;
	
	get_odd_even_rec(t, &odd, &even);
    printf("Even elements:\n");
	println_list(even);
    free_list(even);
	printf("Odd elements:\n");
	println_list(odd);
    free_list(odd);
	
    // (e) todo: implement
	Node* list = NULL;
    
    // ... filter_tree(t, ...);
    println_list(list);
    free_list(list);
	
	
    // (f) todo: check:
	BTNode* t_sorted = NULL;
	
	printbln(is_sorted(NULL));
    test_equal_b(is_sorted(NULL), true);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, NULL, NULL);
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), true);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, 
				new_btnode(55, NULL, NULL), 
                new_btnode(55, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), false);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, 
				new_btnode(48, NULL, NULL), 
                new_btnode(55, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), false);
    free_tree(t_sorted);
	
	t_sorted = new_btnode(48, 
				new_btnode(1, NULL, NULL), 
                new_btnode(6, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), false);
    free_tree(t_sorted);
	
		t_sorted = new_btnode(48, 
				new_btnode(1, NULL, NULL), 
                new_btnode(57, NULL, NULL));
	
    printbln(is_sorted(t_sorted));
    test_equal_b(is_sorted(t_sorted), true);
    free_tree(t_sorted);
	
	
    
    BTNode* t3 = new_btnode(48, 
        new_btnode(11, 
            new_btnode(5, 
                new_btnode(1, NULL, NULL), 
                new_btnode(6, NULL, NULL)), 
            new_btnode(30, 
                new_btnode(29, NULL, NULL), 
                NULL)), 
        new_btnode(57, 
            new_btnode(51, 
                new_btnode(50, NULL, NULL), 
                NULL), 
            new_btnode(99, 
                NULL, 
                new_btnode(100, NULL, NULL))));
    printbln(is_sorted(t3));
    test_equal_b(is_sorted(t3), true);
    free_tree(t3);

    BTNode* t4 = new_btnode(10, 
        new_btnode(11, 
            new_btnode(20, 
                new_btnode(21, NULL, NULL), 
                new_btnode(20, NULL, NULL)), 
            new_btnode(30, 
                new_btnode(31, NULL, NULL), 
                NULL)), 
        new_btnode(20, 
            new_btnode(40, 
                new_btnode(50, NULL, NULL), 
                NULL), 
            new_btnode(30, 
                NULL, 
                new_btnode(100, NULL, NULL))));
    printbln(is_sorted(t4));
    test_equal_b(is_sorted(t4), false);
    free_tree(t4);
    free_tree(t4);

    free_tree(t);

    return 0;
}
