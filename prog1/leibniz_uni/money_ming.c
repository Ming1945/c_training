/*
Compile: make money
Run: ./money
make money && ./money
*/

#include "base.h"


const double BITCOIN_USD = 4273.38; // 1 Bitcoin = 4273.38 USD
const double EURO_USD = 1.14; 		// 1 EURO = 1.14 USD
const double DKK_USD = 0.15; 		// 1 Dansk Krone (DKK) = 0.15 USD

enum Currency { BITCOIN, DOLLAR, EURO, DANSK_KRONE }; 
typedef enum Currency Currency;

struct Money { double amount; Currency currency; }; 
typedef struct Money Money;

// double, Currency -> Money
// Initialize a Money structure.
Money make_money(double amount, Currency currency) {
    Money m = { amount, currency };
    return m;
}

// int Money, Money, double -> bool
// Test wheather the actual value of the money is within +/- tolerance of the expected value of the money.
bool test_value(int line, Money a, Money e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.currency, e.currency);
    return x && u;
}

void print_money(Money m);

void print_money_test() {
    print_money(make_money(1234, DOLLAR));
    print_money(make_money(1.234, BITCOIN));
    print_money(make_money(1.34, EURO));
    print_money(make_money(27.50, DANSK_KRONE));
}

// Money -> void
// Print the ammount of money.
void print_money(Money m) {
    switch (m.currency) {
        case DOLLAR : printf("%.2f $ \n" , m.amount); break;
        case BITCOIN : printf("%.8f Bitcoin \n" , m.amount); break;
        case EURO : printf("%.2f Euro \n" , m.amount); break;
        case DANSK_KRONE : printf("%.2f Dansk Krone \n" , m.amount); break;
    }
}

Money to_currency(Money m, Currency currency);

void to_currency_test(void) {
    test_value(__LINE__, to_currency(make_money(1, BITCOIN), DOLLAR), make_money(4273.38, DOLLAR), 1e-2);
    test_value(__LINE__, to_currency(make_money(1, DOLLAR), EURO), make_money(0.87, EURO), 1e-2);
    test_value(__LINE__, to_currency(make_money(1, EURO), DANSK_KRONE), make_money(7.60 , DANSK_KRONE), 1e-2); 
    test_value(__LINE__, to_currency(make_money(1, DANSK_KRONE), DOLLAR), make_money(0.15, DOLLAR), 1e-2);
    test_value(__LINE__, to_currency(make_money(1, EURO), DOLLAR), make_money(1.14, DOLLAR), 1e-2); 
}

// Money, Currency -> Money
// Convert an amount of money to the given target currency.
Money to_currency(Money m, Currency target_currency) {
    // todo: implement
    switch (m.currency) {
        case DOLLAR : 
            switch (target_currency) {
                case DOLLAR : return make_money(m.amount , DOLLAR); break;
                case EURO : return make_money(m.amount / EURO_USD , EURO); break;
                case BITCOIN : return make_money(m.amount / BITCOIN_USD, BITCOIN); break;
                case DANSK_KRONE : return make_money(m.amount / DKK_USD, DANSK_KRONE); break; 
            } break;
        case EURO : 
            switch (target_currency) {
                case DOLLAR : return make_money(m.amount * EURO_USD , DOLLAR); break;
                case EURO : return make_money(m.amount , EURO); break;
                case BITCOIN : return make_money(m.amount * EURO_USD / BITCOIN_USD , BITCOIN); break;
                case DANSK_KRONE : return make_money(m.amount * EURO_USD / DKK_USD , DANSK_KRONE); break; 
            } break;
        case BITCOIN : 
            switch (target_currency) {
                case DOLLAR : return make_money(m.amount * BITCOIN_USD, DOLLAR); break;
                case EURO : return make_money(m.amount * BITCOIN_USD / EURO_USD , EURO); break;
                case BITCOIN : return make_money(m.amount , BITCOIN); break;
                case DANSK_KRONE : return make_money(m.amount * BITCOIN_USD / DKK_USD, DANSK_KRONE); break; 
            } break;
        case DANSK_KRONE : 
            switch (target_currency) {
                case DOLLAR : return make_money(m.amount * DKK_USD, DOLLAR); break;
                case EURO : return make_money(m.amount * DKK_USD / EURO_USD , EURO); break;
                case BITCOIN : return make_money(m.amount * DKK_USD / BITCOIN_USD, BITCOIN); break;
                case DANSK_KRONE : return make_money(m.amount , DANSK_KRONE); break; 
            } break;
    }
    return make_money(0, EURO);
}

int compare(Money m, Money v);

void compare_test(void) {
	test_equal_i(compare(make_money(1000, DOLLAR), make_money(877.19, EURO)), 0); //LAST ERROR
	test_equal_i(compare(make_money(1000, EURO), make_money(500, DOLLAR)), 1);
	test_equal_i(compare(make_money(100, DANSK_KRONE), make_money(250, BITCOIN)), -1);
	test_equal_i(compare(make_money(1, BITCOIN), make_money(3500, EURO)), 1);
	test_equal_i(compare(make_money(100, EURO), make_money(1000, DANSK_KRONE)), -1);    
}
    
// Money, Money -> int
// Compares two amounts of money. Returns 0 if the two amount of money are equal, 
// -1 if w is smaller than v and +1 otherwise.
int compare(Money m, Money v) {
    // todo: implement. May use the fabs function. fabs(double input) returns the absolute value of input.
    Money a = to_currency(m,DOLLAR);
    Money b = to_currency(v,DOLLAR);
    if (round(a.amount) > round(b.amount)) return 1;
    else if (round(a.amount) < round(b.amount)) return -1;
    return 0;
}

int main(void) {
	printf("%.2f\n", 22.3);
    
    printf("\n ====== Tests for currency printing starts here ====== \n \n");
    print_money_test();

    printf("\n ====== Tests for currency conversion starts here ====== \n \n");
    to_currency_test();
    
    printf("\n ====== Tests for currency comparison starts here ====== \n \n");
    compare_test();
    
    return 0;
}
