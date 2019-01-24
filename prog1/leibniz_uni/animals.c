#include "base.h"
/*
Compile: make animals
Run: ./animals
make animals && ./animals
*/

enum AnimalType { UNKNOWN_TYPE , DOG_TYPE , CAT_TYPE , SHARK_TYPE }; 
typedef enum AnimalType AnimalType;

struct Dog {
    double neckBandLength;
}; typedef struct Dog Dog;

struct Cat {
    bool wool;
}; typedef struct Cat Cat;

struct Shark {
    int surfers;
    bool hungry;
}; typedef struct Shark Shark;

//todo: variant datatype. Use the enum above to identify an animal. Store in this struct common variables for all animals. 
struct Animal { 
    String name;
    enum AnimalType animalType;
    double weightKilograms;
    union {
        struct Dog dog;
        struct Cat cat;
        struct Shark shark;
    };
}; typedef struct Animal Animal;

struct Animal make_animal(String name, double weightKilograms) {
    //todo: implement
    struct Animal animal;
    animal.animalType = UNKNOWN_TYPE;
    animal.name = name;
    animal.weightKilograms = weightKilograms;
	return animal;
}

//todo: implement make_... functions for cat and white shark
struct Animal make_dog(String name , double weightKilograms , double neckBandLength){
    struct Animal animal = make_animal(name, weightKilograms);
    animal.dog.neckBandLength = neckBandLength;
    animal.animalType = DOG_TYPE;
	return animal;
}

struct Animal make_cat(String name , double weightKilograms , bool wool){
    struct Animal animal = make_animal(name, weightKilograms);
    animal.cat.wool = wool;
    animal.animalType = CAT_TYPE;
	return animal;
}

struct Animal make_shark(String name , double weightKilograms , int surfers , bool hungry){
    struct Animal animal = make_animal(name, weightKilograms);
    animal.shark.hungry = hungry;
    animal.shark.surfers = surfers;
    animal.animalType = SHARK_TYPE;
    return animal;
}

void print_animal(struct Animal animal) {

    if (animal.animalType == DOG_TYPE){
        printf("\n I'm a dog , my name is %s and I weigh %.2f kg. my neckBandLength is %f m . \n" , animal.name , animal.weightKilograms , animal.dog.neckBandLength);
    
    } if (animal.animalType == CAT_TYPE){
        printf("\n I'm a pussy cat , my name is %s and I weigh %.2f kg and " , animal.name , animal.weightKilograms);
        if(animal.cat.wool){
            printf("I like Wool! \n");
        } 
        else {
            printf("I don't like Wool! \n");
        }
    
    } if (animal.animalType == SHARK_TYPE){ 
        printf("\n I'm a white shark, my name is %s and I weigh %.2f kg. I've eaten %d surfers and now " , animal.name , animal.weightKilograms , animal.shark.surfers);
        if(animal.shark.hungry){
            printf("I am Hungry! \n");
        } 
        else {
            printf("I am not Hungry! \n");
        }	
    }

}


int main(void) {
    printf("\n");

    struct Animal dog1 = make_dog("KONTOL ANJING", 32.12345678, 15);
    print_animal(dog1);
   
    struct Animal cat1 = make_cat("KUCING BAJINGAN", 20.999, true);
    print_animal(cat1);
    
    struct Animal shark1 = make_shark("HIU NGENTOT", 1945.236654 , 999 , false);
    print_animal(shark1);
    
    printf("\n");
    
    return 0;
}