/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"

// a) struct Statistics ...
struct Statistics  {
	int year;
	int men;
	int women;
	double height_men;
	double height_women;
}; typedef struct Statistics Statistics;

// b) ... make_statistics...
struct Statistics make_statistics (int year , int men , int women , double height_men , double height_women) {
	struct Statistics s;
	s.year = 0;
	s.men = 0;
	s.women = 0;
	s.height_men = 0.0;
	s.height_women = 0.0;
	return s;
}

// c) ... print_statistics...
void print_statistics (Statistics s) {
	printf("\nmean year : %d \t \t \t \n" , s.year);
	printf("number males : %d \t \t \n" , s.men);
	printf("number females : %d \t \n" , s.women);
	printf("mean height males : %.2f \t \n" , s.height_men);
	printf("mean height females : %.2f \t \n" , s.height_women);
}
// d) ... compute_statistics...
void compute_statistics(String table) {
	struct Statistics statistics = make_statistics(0, 0, 0, 0.0, 0.0);
	int length = s_length(table);
	int j = 15;
	while (j < length) { //geht mit (j != EOF) ?
		
		String stringYear = s_sub(table, j, j + 5);
		//printf(" xxxxx %s", stringYear);
		int intYear = i_of_s(stringYear);
		statistics.year += intYear;

		String sex = s_sub(table, j + 6, j + 7);

		String stringHeight = s_sub(table, j + 8, j + 12);
		
		if(s_equals(sex, "m")) {
			statistics.men++;
			double intHeight = d_of_s(stringHeight);
			statistics.height_men += intHeight;
		}
		else if(s_equals(sex, "f")) {
			statistics.women++;
			double intHeight = d_of_s(stringHeight);
			statistics.height_women += intHeight;
		}
		j+=12;
		
	}

	statistics.year /= (statistics.men+statistics.women);
	statistics.height_men /= statistics.men;
	statistics.height_women /= statistics.women;

	print_statistics(statistics);
}

int main(void) {
	String table = s_read_file("people.txt");
	//printsln(table);
	compute_statistics(table);
	return 0;
}
