//
// Created by Patryk on 12.04.2018.
//

#ifndef KOMBAIIN_KLIENT_H
#define KOMBAIIN_KLIENT_H

#include "constants.h"
#include "produkt.h"

struct KLIENT{
    std::string nazwisko;
    std::string mail;
    std::string numer_zamowienia;
    std::string produkty_kopia[ILE_PRODUKTOW];
    std::string adres_klienta[10];
    std::string adres_dostawy[10];
    std::string termin_dostawy;
    std::string termin_platnosci;
    std::string termin_wystawienia_dokumentu;
    std::string telefon;
    std::string forma_platnosci;
    std::string data;
    std::string numer_faktury;
    std::string sciezka_do_kopii_faktury;
    std::string kwota_vat;
    std::string kwota_netto;


    PRODUKT produkty[ILE_PRODUKTOW];

    double kwota_brutto;
    int forma_dostawy;
    int numer_paragonu;

    /*  0 - odbior osobisty
        1 - przesylka */
};


#endif //KOMBAIIN_KLIENT_H
