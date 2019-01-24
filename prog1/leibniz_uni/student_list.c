/*
Compile: make student_list
Run: ./student_list
make student_list && ./student_list
*/

#include "pointer_list.h"

// Data definition for a student
typedef struct {
	String name;
	String sex;
	int mat_nr;
	double debts;
} Student;



// String, String, int, double -> City*
// Create a student (constructor).
Student* new_student(String name, String sex, int mat_nr, double debts) {
    Student* s = xcalloc(1, sizeof(Student));
    s->name = s_copy(name);
    s->sex = s_copy(sex);
	s->mat_nr = mat_nr;
    s->debts = debts;
	return s;
}

// Student* -> Student*
// Create a copy of student.
void* copy_student(void* x) {
    // todo: implement
    Student* s = (Student*)x;
    return new_student(s->name, s->sex, s->mat_nr, s->debts);
}

// Student* -> String
// String representation of student in the form:
// s is a hard working student who is in debt for debts €. The matriculations number is mat_nr and the students sex is sex
String student_to_string(void* x) {
    Student* s = (Student*) x;
    int n = s_length(s->name) + s_length(s->sex) + 150;
    String text = xmalloc(n);
    snprintf(text, n, "%s is a hard working student who is in debt for %.2f Euro. The matriculation number is %d and the students sex is %s", s->name, s->debts, s->mat_nr, s->sex);
    return text;
}

// Student* -> void
// Releases memory of a student.
void free_student(void* x) {
    // todo: implement
    Student* s = (Student*)x;
    free(s->name);
    free(s->sex);
    //free(s->mat_nr);
    //free(s->debts);
    free(s);
}

// Student* -> bool
// Returns true if the amount of debts is above 20000.
bool poor_student(void* element, int i, void* x) {
    // todo: implement
    Student* s = (Student*)element;
    if(s->debts > 20000) {
        return true;
    }

	return false;
}

// Student* -> bool
// Returns true if the matriculation number is shorter than *x.
bool mat_nr_less_digits_than(void* element, int i, void* x) {
    // todo: explain each line
    Student* s = (Student*)element; // defines that element contains all element of Student
    int* a = (int*)x; // x is typecasted as pointer integer
	int counter = 0; // to count the digits
	for(int i = s->mat_nr; i > 0; i = i / 10 )//after each count, mat_nr will be divided by 10
		counter++; //counter value added by 1
    return (counter < (*a)); // return true if counter is smaller than pointer a.
}

// Student* -> String
// Maps a student to its name.
void* student_name(void* element, int i, void* x) {
	//todo: implement
    Student* s = (Student*)element;
    return s->name;
}

// Student*, int, double* -> Student*
// Creates a new student with less debts. x is in range of [0, 1].
void* pay_debts(void* element, int i, void* x){
	// todo: implement
    Student* s = (Student*)element;
    double discount = *(double*)x;
    s->debts -= (s->debts * discount);
    return s;
   
}

// double*, Student*, int -> void
// Adds students debts to state.
void add_debts(void* state, void* element, int index) {
    // todo: explain each line
    double* a = (double*)state; // defines variable void* state from parameter to variable double *a
    Student* s = (Student*)element; // defines variable Student* element from parameter to variable Student* s
    *a = *a + s->debts; // now a is the sum of a itself with s->debts
}

typedef struct {
	int n;
	double debts;
}Student_stats;

// Student_stats**, Student*, int -> void
// Computes the average debts for students.
void student_stats(void* state, void* element, int index) {
    // todo: explain each line
    Student_stats** s = (Student_stats**) state; // ...
    Student* e = (Student*) element; // defines variable Student* element from parameter to variable Student* e
    if(*s == NULL){ // ...
		*s = xmalloc(sizeof(Student_stats)); // alocates dinamycal memory for *s from Student_stats
		(*s)->n = 0; // declares that the value of pointer s n is 0
		(*s)->debts = 0.0; // // declares that the value of pointer s debts is 0
	}
	(*s)->n++;
	(*s)->debts += e->debts;
}

// Student*, Student* -> { <0, 0, >0 }
// Returns =0 if x and y are equal, <0 if x smaller than y, >0 otherwise.
int cmp_student_mat_nr(void* x, void* y) {
    // todo: implement
    Student* a = (Student*)x;
    Student* b = (Student*)y;
    if (a->mat_nr > b->mat_nr) return 1;
    if (a->mat_nr < b->mat_nr) return -1;
    return 0;
}

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

// String -> void
// Releases a string.
void free_string(void* x) {
    free(x);
}

int main(void) {
    base_init();
    base_set_memory_check(true);
	
	Student* s1 = new_student("Mina", "not binary", 2090, 15000.00);
    Student* s2 = new_student("Mike", "male", 208080, 23607.56);
	Student* s3 = new_student("Anna", "female", 42, 406.26);
	Student* s4 = new_student("Jimmy", "male", 133, 8000.90);
	
    Node* list = new_node(s1, new_node(s2, new_node(s3, new_node(s4, NULL))));
    println_list(list, student_to_string);
    
    // find first poor student, use find_list
    // print result, if any
    printsln("first poor student:");
    Student* found_student = find_list(list, poor_student, NULL);
    if(found_student != NULL) {
        String s = student_to_string(found_student);
        printsln(s);
        free(s);
    }
    // find the first student with a matriculation number with a length less than max_digits, use find_list
    // print result, if any
    printsln("first student with mat_nr digit count less than max_digits:");
    int max_digits = 8;
    // todo: implement
    found_student = find_list(list, mat_nr_less_digits_than, &max_digits);
    if(found_student != NULL) {
        String s = student_to_string(found_student);
        printsln(s);
        free(s);
    }

    // map the list of students to a list of student names
    printsln("student names:");
    // todo: implement
    Node* names = map_list(list, student_name, NULL);
    println_list(names, string_to_string);
    free_list(names, NULL);

    // reduce the amount of debts for all students by 15%
    // new list, do not modify original list elements, use map_list
    printsln("reduce debts:");
    double factor = 0.15;
    // todo: implement
    Node* list2 = map_list(list, pay_debts, &factor);
    println_list(list2, student_to_string);
    free_list(list2, NULL);
    
    // find all students with matriculation numbers with less than 4 digits, use filter_list
    printsln("short matriculation numbers:");
    // todo: implement
	int shortNum = max_digits / 2;
    Node* selected_students = filter_list(list, mat_nr_less_digits_than, &shortNum);
    println_list(selected_students, student_to_string);
    free_list(selected_students, NULL);
    
    // produce a list of the names students with short matricultion numbers, use filter_map_list
    printsln("names of students with short matriculation numbers:");
    // todo: implement
    Node* listy = filter_map_list(list, mat_nr_less_digits_than, student_name, &shortNum);
    println_list(listy, string_to_string);
    free_list(listy, NULL);
    // compute the sum of the debts of all students, use reduce_list
    printsln("total debts:");
    double total_debts = 0;
    reduce_list(list, add_debts, &total_debts);
    printdln(total_debts);


	
    // calculate the average debts, use reduce_list
    Student_stats* stats = NULL;
    reduce_list(list, student_stats, &stats);
    if (stats != NULL) {
        //String s = student_to_string(stats);
        printf("The average debts are: %.2f\n", stats->debts/stats->n);
        free(stats);
    }
    
    // sort the students by their matriculation number, in increasing order
    // use insert_ordered, do not modify the original list, do not copy the students
    Node* sorted_list = NULL;
    // todo: implement
    for (Node* n = list; n != NULL; n = n->next) {
        sorted_list = insert_ordered(sorted_list, n->value, cmp_student_mat_nr);
    }
    printsln("sorted students:");
    if (sorted_list != NULL) {
        println_list(sorted_list, student_to_string);
        free_list(sorted_list, NULL);
    }

    // free all memory
    free_list(list, free_student);
    
    return 0;
}
