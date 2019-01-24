/*
Compile: make lists
Run: ./lists
make lists && ./lists
*/

#include "base.h"

// Represents a single list node. The string value is dynamically allocated. 
// The node is the owner of the value and has to free it when released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(", %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// True iff c is whitespace.
bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// Skip spaces starting at index i.
char* skip_whitespace(char* s) {
    while (is_whitespace(*s)) s++;
    return s;
}

// Skip token starting at index i.
char* skip_token(char* s) {//
    while (*s != '\0' && !is_whitespace(*s)) s++;
    return s;
}

// todo: describe implementation
// Creates a list of strings from a string of tokens, which are separated by whitespace.
// e.g., "a bb ccc" is converted to "a" --> "bb" --> "ccc" --> NULL
Node* to_list(String a) {
    if (a == NULL) return NULL;
    Node* first = NULL;
    Node* last = NULL;
    char* b;
    while (*a != '\0') {
        a = skip_whitespace(a);//the spaces in String a will be skipped
        if (*a == '\0') break;
        b = skip_token(a);
        char* s = s_sub(a, 0, b-a); // s_sub result is dynamically allocated
        if (first == NULL) {
            first = new_node(s, NULL); // new_node creates a dynamic copy of s
            last = first;
        } else {
            last->next = new_node(s, NULL); // new_node creates a dynamic copy of s
            last = last->next;
        }
        free(s); // can free s, because new_node has its own copy
        a = b;
    }
    return first;
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    // todo: implement
    Node* node_next = NULL;
    for (Node* node = list; node != NULL; node = node_next) {//the next index NULL
        node_next = node->next;//if the next index is NULL, it will skip to the next element
        free(node->value);
        free(node);
    }
}

bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
    printf("\n==========Test Equal Lists Test==========\n\n");
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    // todo: implement
    int count1 = 0;
    int count2 = 0;
    for (Node* node = list1; node != NULL; node = node->next) {
        count1++;
    }
    for (Node* node = list2; node != NULL; node = node->next) {
        count2++;
    }

    if (count1 == count2) {
        int index = 0;
        while (list1 != NULL && list2 != NULL) {
            if (!s_equals(list1->value, list2->value)) {
                printf("Line %d: the value at node %d differ: %s <-> %s\n", line, index, list1->value, list2->value);
                return false;
            }
            index++;
            list1 = list1->next;
            list2 = list2->next;
        }
        printf("Line %d: The lists are equal\n", line);
        return true;
    } else {
        if(count1 > count2) {
            printf("Line %d: list1 is longer than list2\n", line);
        } else {
            printf("Line %d: list1 is shorter than list2\n", line);
        }
        return false;
    }
}

void to_list_test(void) {
    printf("\n==========To List Test==========\n\n");
    Node* actual = NULL;
    Node* expected = NULL;
    actual = to_list(NULL);
    test_equal_lists(__LINE__, actual, expected);

    actual = to_list(" a bb");
    expected = new_node("a", new_node("bb", NULL));
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);
    
    // todo: add three more tests
    actual = to_list("1 2 3 4");
    expected = new_node("1", new_node("2", new_node("3", new_node("4", NULL))));
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    actual = to_list("Hi my name is Josh ");
    expected = new_node("Hi", new_node("my", new_node("name", new_node("is", new_node("Josh", NULL)))));
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    actual = to_list("can   u count  all    the spaces?");
    expected = new_node("can", new_node("u", new_node("count", new_node("all", new_node("the", new_node("spaces?", NULL))))));
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);
}

int char_count_in_list(Node* list, char c);

// Example calls for char_count_in_list (below).
void char_count_in_list_test(void) {
    printf("\n==========Char Count in List Test==========\n\n");
    Node* list = NULL;
    test_equal_i(char_count_in_list(list, 'x'), 0);
    list = new_node("hello", NULL);
    test_equal_i(char_count_in_list(list, 'x'), 0);
    test_equal_i(char_count_in_list(list, 'e'), 1);
    test_equal_i(char_count_in_list(list, 'l'), 2);
    free_list(list);
    list = new_node("hello", new_node("world", NULL));
    test_equal_i(char_count_in_list(list, 'x'), 0);
    test_equal_i(char_count_in_list(list, 'o'), 2);
    test_equal_i(char_count_in_list(list, 'l'), 3);
    free_list(list);
}

// Number of occurrences of c across all strings of the list.
int char_count_in_list(Node* list, char c) {
    // todo: implement
    int counter = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        String string = node->value;
        for (int i = 0; i < s_length(string); i++) {
            if(string[i] == c) {
                counter++;
            }
        }
    }
    return counter;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    printf("\n==========Remove List Test==========\n\n");
    
    Node* list = NULL;
    Node* expected = NULL;
    
    list = new_node("hello", new_node("how", new_node("are", new_node("you", NULL))));
    list = remove_list(list, 0);
    expected = new_node("how", new_node("are", new_node("you", NULL)));
    test_equal_lists(__LINE__, list, expected);
    free_list(list); free_list(expected);
    
    // todo: add three more test examples

    list = new_node("I", new_node("am", new_node("fine", new_node("thanks!", NULL))));
    list = remove_list(list, 2);
    expected = new_node("I", new_node("am", new_node("thanks!", NULL)));
    test_equal_lists(__LINE__, list, expected);
    free_list(list); free_list(expected);

    list = new_node("My", new_node("name", new_node("is", new_node("Josh!", NULL))));
    list = remove_list(list, 1);
    expected = new_node("My", new_node("is", new_node("Josh!", NULL)));
    test_equal_lists(__LINE__, list, expected);
    free_list(list); free_list(expected);

    list = new_node("I", new_node("am", new_node("fine", new_node("thanks!", NULL))));
    list = remove_list(list, 3);
    expected = new_node("I", new_node("am", new_node("fine", NULL)));
    test_equal_lists(__LINE__, list, expected);
    free_list(list); free_list(expected);

}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // todo: implement
    int length = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        length++;
    }
    if (index < 0) {
        return list;
    }
    if(index == 0){
        return list->next;
    }
    Node* node = list;
    int a = 1;
    while(node != NULL && a < index ){
        node = node->next;
        a++;
    }
    if(node->next->next != NULL){
        free(node->next);
        node->next = node->next->next;//remove element at asked index
        return list;
    } else {
        free(node->next); //to remove the element in the last index
        node->next = NULL;
        return list;
    }
    return NULL;
}

Node* insert_in_list(Node *list, Node* list_to_insert, int position);

void insert_in_list_test(void) {
    printf("\n==========Insert in List Test==========\n\n");
    Node *list, *list_to_insert, *expected, *actual;
    list = to_list("a b c");
    actual = insert_in_list(list, NULL, 1);
    expected = to_list("a b c");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    actual = insert_in_list(NULL, list, 1);
    expected = to_list("a b c");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    list_to_insert = to_list("x y");
    actual = insert_in_list(list, list_to_insert, -1);
    expected = to_list("x y a b c");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    list_to_insert = to_list("x y");
    actual = insert_in_list(list, list_to_insert, 0);
    expected = to_list("x y a b c");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    list_to_insert = to_list("x y");
    actual = insert_in_list(list, list_to_insert, 1);
    expected = to_list("a x y b c");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    list_to_insert = to_list("x y");
    actual = insert_in_list(list, list_to_insert, 2);
    expected = to_list("a b x y c");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    list_to_insert = to_list("x y");
    actual = insert_in_list(list, list_to_insert, 3);
    expected = to_list("a b c x y");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);

    list = to_list("a b c");
    list_to_insert = to_list("x y");
    actual = insert_in_list(list, list_to_insert, 4);
    expected = to_list("a b c x y");
    test_equal_lists(__LINE__, actual, expected);
    free_list(actual); free_list(expected);
}

Node* insert_in_list(Node *list, Node* list_to_insert, int position) {
    // todo: implement

    if (list == NULL) {
       return list_to_insert;
    }

    int length = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        length++;
    }

    Node* new = list_to_insert;
    Node* node = list;
    int index = 1;
    while(new != NULL) {
        /*if(position <= 0) {
            println_list(new_node(new->value, list));
            node = new_node(new->value, node->next);
        }*/
        while(node != NULL && index < position) {
            node = node->next;
            index++;
        }
        if(node != NULL) {
            node->next = new_node(new->value, node->next);
            println_list(list);
            node = node->next;
        }
        new = new->next;

    }
    /*while(new != NULL) {


        if(position > length) {
            while (node->next != NULL) node = node->next;
            node->next = new_node(new->value, NULL);
            node = node->next;
        }
        new = new->next;
        println_list(list);
    }*/

    return list;
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
    base_init();
    base_set_memory_check(true);

    test_equal_lists_test();
    char_count_in_list_test();
    to_list_test();
    remove_list_test();
    insert_in_list_test();
    return 0;
}
