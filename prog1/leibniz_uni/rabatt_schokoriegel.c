#include <base.h>

int Preis (int menge) {
    int preis;
    int schoko = 50;
    if (menge < 1) preis = 0; 
    else if (menge >= 10 && menge < 100) preis = schoko * menge * 0.9;
    else preis = schoko * menge * 0.8; 
    return preis;
}

int Gesamtpreis (int preis) {
    int gesamtpreis = 0;
    if (preis < 2000 && preis > 0) gesamtpreis = preis + 500;
    else if (preis >= 2000) gesamtpreis = preis;
    else return gesamtpreis; //setelah else selalu di return sonst dia ga ngapa"in , karna gesamtpreisnya gesamtpreis dari preis,bukan gesamtpreis = 0   
    return gesamtpreis;
}

void Gesamtpreis_test() {
    test_equal_i(Gesamtpreis(Preis(0)) , 0);
    test_equal_i(Gesamtpreis(Preis(20)) , 1400);
    test_equal_i(Gesamtpreis(Preis(200)) , 8000);
}


int main (void) {
    Gesamtpreis_test();
    return 0;
}