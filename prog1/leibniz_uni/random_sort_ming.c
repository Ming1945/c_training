/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/

#include "base.h"
#include <math.h>

//template code

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;


struct Car{
	char* brand;
	int year;
	int km;
	double price;
};

typedef struct Car Car;

//print car information
void print_car(Car* car){
	printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);	
}

//print carArray
void print_car_array(Car* car_park, int car_count){
	for(int i = 0; i < car_count; i++){
		print_car(car_park + i);
	}
}


// Creates an array with random cars. Returns a pointer to the array.
Car* create_car_park(int car_count){
	//next statement is part of the following lectures. Don't worry.
	Car* car = (Car*) xmalloc(sizeof(Car) * car_count);
	
	//fill the array with random cars
	for(int i = 0; i < car_count; i++){
		int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

		car[i].brand = brands[random_brand_index];
		int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
		car[i].year = random_year;
		
		int random_km = 0;
		// On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
		if(RAND_MAX == 32767){
			random_km = (i_rnd(max_km >> 16) << 16 ) | i_rnd(max_km); //dirty hack
		}else{
			random_km = i_rnd(max_km); 
		}
		car[i].km = random_km; //max 250.000km
		
		car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) + 20000.00 * pow(0.75, random_km / 10000.0)  ; // car price max 50.000 Euro
	}
	return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
}

//end of template code

//now it is your turn ... 

// (a) todo: implement compare function
int compare(Car car1, Car car2) {
	if (car1.year < car2.year) return -1; //if car1.year younger than car2.year then return -1
	if (car1.year > car2.year) return 1; //if car1.year younger than car2.year then return 1
	//else {
	if (car1.year == car2.year && car1.brand == car2.brand) {
         return 0;
    } 
	else {
        int cmp = strcmp(car1.brand, car2.brand);
        return cmp;
    }
}

// (b) todo: write compare test function

Car make_car (char* brand, int year, int km, double price) { //we define a new car with this attributes , so that it could be easily compare
    Car c = {brand, year, km, price };
    return c;
}

void compare_test (void) {
    Car m = { "Fiat" , 1994 , 20 , 12500 };
    Car i = { "BMW" , 1998 , 10 , 10000 };
    Car n = { "VW" , 2017, 60 , 15000 };
    Car g = { "VW" , 2017 , 50 , 20000 };
    
    test_equal_i(compare(i,g), -1);
    test_equal_i(compare(n,m), 1);
    test_equal_i(compare(n,g), 0);
    test_equal_i(compare(m,i), -1);
    test_equal_i(compare(i,m), 1);   
}


// (c) todo: implement sorted function
bool sorted(Car* a, int length) {
	for (int i = 0 ; i <= length - 1 ; i++) {
		int result = compare(a[i] , a[i+1]);
		if (result < 0) return false; //we assume that the cars are sorted in descending order. otherwise (result > 0) but you have to change compare_cars function too 
	}
	return true;
}

// (d,e) todo: implement random_sort function
int random_sort(Car* a, int length) {
	// we use bubble sort algortihm but instead of compare the current car and the next one , we compare 2 random indexes in this array 
	int swapCounter = 0;
	int x = i_rnd(length);
	int y = i_rnd(length);
	if (compare(a[x] , a[y]) < 0) { //if random index of array Car* a return - 1 , then it's time to sorting
		Car z = a[x] ;
		a[x] = a[y];
		a[y] = z;
		swapCounter++; // I think this one is KLAR(?) , right?
	}
	return swapCounter;
}


int main(void) {
	// (b) todo: test compare function
	compare_test();
	
	//some output
	int number_of_random_cars = i_rnd(7) + 3;
	int c1 , c2 , c3 , c4 , c5;

	for (int i = 0; i < 5; i++) {
	Car* car_park = create_car_park(number_of_random_cars);
	printf("Sorting...\n");
	//todo: sort the car_park array.
	int swapTotal = random_sort(car_park , number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	printf("Total swaps : %d \n" , swapTotal);
	    switch (i) {
	        case 0: 
                c1 = swapTotal;
            case 1: 
                c2 = swapTotal;
            case 2:
                c3 = swapTotal;
            case 3:
                c4 = swapTotal;
            case 4:
                c5 = swapTotal;
        }
		delete_car_park(car_park);
	}
	
	// (f) todo: compare the number of swaps and compare calls.
	printf("\n1st swap = %d\n", c1);
    printf("2nd swap = %d\n", c2);
    printf("3th swap = %d\n", c3);
    printf("4th swap = %d\n", c4);
    printf("5th swap = %d\n", c5); 
	
	double swapsAverage = (c1 + c2 + c3 + c4 + c5) / 5;
	printf("The average swaps is : %lf\n", swapsAverage);
    
	return 0;
}
