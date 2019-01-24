// make characters_test && ./characters_test

#include "character.h"
#include "fighter.h"
#include "wizard.h"
#include "object_list.h"

// (c) todo: implement
// Aggregate a list: state is the intermediary aggregation result, element is the current element.
void add_attack(void* state, void* element, int index) {
    // implement
    double* atkNow = (double*)state;
    Character* atk = (Character*)element;
    *atkNow += atk->class->attack(atk);
}

// (d) todo: implement
// Check whether element satisfies a predicate.
bool is_wizard(void* element, int i, void* x) {
        Wizard* wiz = (Wizard*)element;
        String name = wiz->class->to_string(wiz);
        //String wizzy = s_sub(name,0,5);
    if(s_get(name , 2) == 'z') {
        free(name);
        return true;
    }
    free(name);
    return false; // implement

    /* statt
    if (s_equals(wizzy, "Wizard")) {
        free(wizzy);
        free(name);
        return true;
    }*/
}

int main(void) {
    base_init();
    base_set_memory_check(true);
    
    Fighter* f1 = new_fighter(1.2, 3.4);
    Fighter* f2 = new_fighter(4.3, 2.1);
    Wizard* w1 = new_wizard(6.5, 1.1);
    Wizard* w2 = new_wizard(5.4, 2.2);

    // (a) uncomment when you have implemented the respective functions in fighter.c and wizard.c
    double a, d;

    String s = f1->class->to_string(f1);
    a = f1->class->attack(f1);
    d = f1->class->defense(f1);
    printf("%s: attack=%.2f, defense=%.2f\n", s, a, d);
    free(s);

    // output attack and defense in the same way for f2, w1, and w2
    // ...
    double a1, d1;
    String s1 = f2->class->to_string(f2);
    a1 = f2->class->attack(f2);
    d1 = f2->class->defense(f2);
    printf("%s: attack=%.2f, defense=%.2f\n", s1, a1, d1);
    free(s1);

    double a2, d2;
    String s2 = w1->class->to_string(w1);
    a2 = w1->class->attack(f1);
    d2 = w1->class->defense(f1);
    printf("%s: attack=%.2f, defense=%.2f\n", s2, a2, d2);
    free(s2);

    double a3, d3;
    String s3 = w2->class->to_string(w2);
    a3 = w2->class->attack(w2);
    d3 = w2->class->defense(w2);
    printf("%s: attack=%.2f, defense=%.2f\n", s3, a3, d3);
    free(s3);
    

    // (b) todo: implement

    Node* list = new_node(f1, new_node(f2, new_node(w1, new_node(w2, NULL))));
    a = 0;
    d = 0;
    // for...
    for (Node* node = list; node != NULL; node = node->next) {
        Character* getClass = node->value;
        a += getClass->class->attack(getClass);
        d += getClass->class->defense(getClass);
    }

    printf("group attack = %.2f, group defense = %.2f (using a for-loop)\n", a, d);

    // (c) todo: implement

    a = 0;
    reduce_list(list, add_attack, &a);
    printf("group attack = %.2f (using reduce list)\n", a);

    // (d) todo: implement

    // Produce a list of those elements of list that satisfy the predicate.
    Node* wizards = filter_list(list, is_wizard, NULL);
    println_list(wizards);
    free_list(wizards, false);

    free_list(list, true);
    
    return 0;
}
