/*
Compile: make mensa
Run: ./mensa
Compile & run: make mensa && ./mensa
*/

#include "base.h"

/**
Represents a single list node. The string value is dynamically allocated. 
The node is the owner of the value and has to free it when released.
*/
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

/**
Create a list node. Copies the value (into dynamically allocated storage).
*/
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

/**
Prints the components of the given list.
*/
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

/**
Print list followed by a newline.
*/
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

/**
Return the number of elements in the list.
*/
int length_list(Node* list) {
    // todo: implement (a)
    if (list == NULL) return 0;
    else {
        return 1 + length_list(list->next);
    }
}

/**
Return the element at position.
*/
String get_list(Node* list, int position) {
    // todo: implement (b)
    if (list == NULL) return NULL;
    else {
        int p = 0;
        for (Node* n = list; n != NULL; n = n->next) {
            if (p == position) {
                return n->value;
            }
            p++;
        } 
        return NULL;
    }
}

/**
Free all nodes of the list, including the values it contains.
*/
void free_list(Node* list) {
    // todo: implement (c)
    Node* node_next = NULL;
    for (Node* node = list; node != NULL; node = node_next) {//the next index NULL
        node_next = node->next;//if the next index is NULL, it will skip to the next element
        free(node->value);
        free(node);
    }
}

/**
Adds an element to the end of the list. Modifies the existing list.
*/
Node* append_list(Node* list, String value) {
    // todo: implement (d)
    if(list == NULL){
        return new_node(value, NULL);
    } else {
        list->next = append_list(list->next, value);
        return list;
    }
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // todo: implement (e)
    if (list == NULL || index < 0) return list;
    if (index == 0) {
        Node* n = list->next;
        free(list->value);
        free(list);
        return n;
    }

    int i = 0;
    Node* node = list;
	while (node != NULL) {
		if (i + 1 == index) {
			Node* remove = node->next;
			if (remove == NULL) return list;
			Node* n = remove->next;
			free(remove->value);
			free(remove);
			node->next = n;
			return list;
		} 
        i++;
        node = node->next;
	}
    return list;
}

/**
Today's menu.
*/
const String menu[] = { "Currywurst", "Spaghetti", "Vegi", "Eintopf", "Salat" };

/**
The number of items on the menu.
*/
const int menu_count = sizeof(menu) / sizeof(char*);

/**
The list of completed food from the kitchen, waiting to be served. Each time a food item is served, the kitchen prepares a new food item randomly from the menu.
*/
Node* food; // List(String)

/**
The list of students standing in line and waiting for food. Each entry contains a string for the food that this student wants.
*/
Node* students; // List(String)

/**
The reputation of the mensa. The player is a staff member of the mensa. The goal of the player is to maximize the reputation of the mensa. Actually serving a dish that was asked for increases the reputation of the mensa by 1. Serving the wrong dish decreases the reputation by 1. If a student asks for a dish that is on the menu but not ready to be served, the reputation of the mensa decreases by 2.
*/
int reputation = 0;

/**
Example output:
fertige Essen: [Spaghetti, Vegi, Salat, Salat, Vegi]
nächster Essenswunsch: Currywurst (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 
*/
void print_situation(void) {
    // todo: implement (f)
    String v = get_list(food, 0);
    String w = get_list(food, 1);
    String x = get_list(food, 2);
    String y = get_list(food, 3);
    String z = get_list(food, 4);
    printf("fertige Essen: [%s, %s, %s, %s, %s]\n", v, w, x, y, z);
    printf("naechster Essenswunsch: %s (%d hungrige Studierende warten)\n", students->value, length_list(students));
    printf("Reputation der Mensa: %d\n", reputation);
}

/**
Print final message, release all dynamically allocated memory, and exit the program.
Fertig für heute. Die Mensa schließt.
Finale Reputation der Mensa: 3
*/
void finish(void) {
    // todo: implement (g)
        printf("Fertig für heute. Die Mensa schließt.\n");
        printf("Finale Reputation der Mensa: %d\n", reputation);
        free_list(food);
        free_list(students);
        exit(0);
}

/**
Run the mensa simulation.

The mensa person then enters the (0-based) index from the list of food. -1 stands for "not available". -2 ends the program. 

Here is an example dialog:

fertige Essen: [Salat, Vegi, Vegi, Spaghetti, Eintopf]
nächster Essenswunsch: Spaghetti (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 3
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Salat, Vegi, Vegi, Eintopf, Eintopf]
nächster Essenswunsch: Spaghetti (3 hungrige Studierende warten)
Reputation der Mensa: 1
> -1
Spaghetti ist nicht da? Schade.
fertige Essen: [Salat, Vegi, Vegi, Eintopf, Eintopf]
nächster Essenswunsch: Salat (2 hungrige Studierende warten)
Reputation der Mensa: -1
> 0
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Vegi, Vegi, Eintopf, Eintopf, Eintopf]
nächster Essenswunsch: Eintopf (2 hungrige Studierende warten)
Reputation der Mensa: 0
> 1
Vegi möchte ich nicht! Ich möchte Eintopf! Dann hole ich mir halt einen Döner!
fertige Essen: [Vegi, Vegi, Eintopf, Eintopf, Eintopf]
nächster Essenswunsch: Currywurst (1 hungrige Studierende warten)
Reputation der Mensa: -1
> 1
Vegi möchte ich nicht! Ich möchte Currywurst! Dann hole ich mir halt einen Döner!
Fertig für heute. Die Mensa schließt.
Reputation der Mensa: -2
*/
void run_mensa(void) {
    // todo: implement
    // create 5 random food items from the menu
    // ...
    for(int i = 0; i < 5; i++) {
        food = append_list(food, menu[i_rnd(menu_count)]);
    }

    // create 3 random food wishes from the menu (each wish from one student)
    // ...
    for (int i = 0; i < 3; i++) {
        students = append_list(students, menu[i_rnd(menu_count)]);
    }

    
    
    print_situation();
    
    int i;
    while ((i = i_input()) >= -1) {
        // process input
        // distinguish different cases, update lists
        if (i >= 0 && i <= 4) {
            if (s_equals(get_list(food, i), get_list(students, 0))) {
                reputation++;
                printf("Vielen Dank! Ich liebe die Mensa!\n");
                food = remove_list(food, i);
                food = append_list(food, menu[i_rnd(menu_count)]);
                students = remove_list(students, 0);
                students = append_list(students, menu[i_rnd(menu_count)]);
            } else {
                reputation--;
                printf("%s moechte ich nicht! Ich möchte %s! Dann hole ich mir halt einen Doener!\n", get_list(food, i), get_list(students, 0));
                food = remove_list(food, i);
                food = append_list(food, menu[i_rnd(menu_count)]);
                students = remove_list(students, 0);
            }
        }
        if (i == -1) {
            reputation -= 2;
            printf("%s ist nicht da? Schade.\n", get_list(students,0));
            students = remove_list(students, 0);
        } 
        // use get_list, remove_list, append_list, length_list
        // use i_rnd to select random food items and random food wishes
        // use s_equals or strcmp to compare strings
        
        print_situation();
    }
    finish();
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    run_mensa();
    return 0;
}
