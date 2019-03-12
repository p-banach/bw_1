//
// Created by Patryk on 12.04.2018.
//

#ifndef KOMBAIIN_PRODUKT_H
#define KOMBAIIN_PRODUKT_H

#include <string>

struct PRODUKT {
    std::string nazwa;
    std::string kod;
    std::string jednostka_sprzedazy;
    std::string vat;

    double cena;
    double cena_za_sztuke;
    double ilosc;
};

#endif //KOMBAIIN_PRODUKT_H
