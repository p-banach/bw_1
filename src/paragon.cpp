//
// Created by Patryk on 12.04.2018.
//

#include <fstream>
#include <iostream>
#include <iomanip>

#include "paragon.h"

double KWOTY_WPLACONE_PER_FORME_PLATNOSCI[ILE_FORM_PLATNOSCI] = { 0, 0 };

void drukujParagon(KLIENT Janek) {

    int numer_paragonu = dajNumerParagonu();
    Janek.numer_paragonu = numer_paragonu;
    double kwota_inna;
    std::ofstream o_paragon;
    std::string nazwa_paragonu = "ZL" + (Janek.numer_zamowienia) + "_NR#" + intToString(numer_paragonu) + ".in";
    std::string sciezka_paragon = SCIEZKA_ZAPISU_PARAGONU + nazwa_paragonu;
    o_paragon.open(sciezka_paragon.c_str());
    int i = 0;

    if ( o_paragon.good()) {
        o_paragon << "#ROLLBACK" << "\n" << "#RECEIPT" << "\n";
        std::cout << std::endl;
        std::cout << "PODGLAD PARAGONU: " << std::endl;
        std::cout << "#ROLLBACK" << "\n" << "#RECEIPT" << "\n";
        while ( Janek.produkty[i].kod != "zzzz" ) {
            std::cout << "#ITEM#" << Janek.produkty[i].nazwa << "#" << std::setprecision(2) << std::fixed
                      << Janek.produkty[i].cena_za_sztuke;
            std::cout << "#" << Janek.produkty[i].ilosc << "#" << Janek.produkty[i].vat;
            std::cout << "#" << Janek.produkty[i].cena << "#" << Janek.produkty[i].jednostka_sprzedazy;
            std::cout << std::endl;
            o_paragon << "#ITEM#" << Janek.produkty[i].nazwa << "#" << std::setprecision(2) << std::fixed
                      << Janek.produkty[i].cena_za_sztuke;
            o_paragon << "#" << Janek.produkty[i].ilosc << "#" << Janek.produkty[i].vat;
            o_paragon << "#" << Janek.produkty[i].cena << "#" << Janek.produkty[i].jednostka_sprzedazy;
            o_paragon << std::endl;
            i++;
        }
        znajdzFormeWTablicy(Janek.forma_platnosci, Janek.kwota_brutto, &kwota_inna);
        std::cout << std::setprecision(2) << std::fixed << "#COMMIT#" << Janek.kwota_brutto << "#"
                  << KWOTY_WPLACONE_PER_FORME_PLATNOSCI[0] << "#" << KWOTY_WPLACONE_PER_FORME_PLATNOSCI[1] << "#1##"
                  << kwota_inna << "#" << Janek.forma_platnosci << "\n";
        o_paragon << std::setprecision(2) << std::fixed << "#COMMIT#" << Janek.kwota_brutto << "#"
                  << KWOTY_WPLACONE_PER_FORME_PLATNOSCI[0] << "#" << KWOTY_WPLACONE_PER_FORME_PLATNOSCI[1] << "#1##"
                  << kwota_inna << "#" << Janek.forma_platnosci << "\n";

        o_paragon << "#CLEARRESULT" << "\n" << "#GETLASTDOCID" << "\n" << "#EXECUTE" << std::endl;

        std::cout << std::endl;
        o_paragon.close();
    } else {
        std::cout << "Nie udalo sie stworzyc pliku paragonu. Uruchom program ponownie." << std::endl;
        getchar();
        exit(0);
    }
}

int dajNumerParagonu() {
    std::fstream io_licznik;
    int numer_paragonu;
    io_licznik.open(SCIEZKA_LICZNIKA.c_str());

    if ( io_licznik.good()) {
        io_licznik >> numer_paragonu;
        int numer_temp;
        numer_temp = numer_paragonu + 1;
        io_licznik.close();
        io_licznik.open(SCIEZKA_LICZNIKA.c_str());
        io_licznik << numer_temp;
        io_licznik.close();
    } else {
        std::cout << "Nie udalo sie otworzyc  pliku \"licznik.txt\". " << std::endl;
        std::cout << "Sprawdz sciezke i stworz go jezeli nie istnieje" << std::endl;
        std::cout << "Po stworzeniu go, uruchom program jeszcze raz" << std::endl;
        std::cout << SCIEZKA_LICZNIKA << std::endl;
        getchar();
        exit(0);
    }
    io_licznik.close();
    return numer_paragonu;
}

void denumerowanie(int numer_paragonu) {
    // dajNumerParagonu paragonow
    std::fstream io_licznik;
    io_licznik.open(SCIEZKA_LICZNIKA.c_str());
    if ( io_licznik.good()) {
        io_licznik >> numer_paragonu;
        int numer_temp;
        numer_temp = numer_paragonu - 1;
        io_licznik.close();
        io_licznik.open(SCIEZKA_LICZNIKA.c_str());
        io_licznik << numer_temp;
        io_licznik.close();
    } else {
        std::cout << "Nie udalo sie otworzyc  pliku \"licznik.txt\". " << std::endl;
        std::cout << "Sprawdz sciezke i stworz go jezeli nie istnieje" << std::endl;
        std::cout << "Po stworzeniu go, uruchom program jeszcze raz" << std::endl;
        std::cout << SCIEZKA_LICZNIKA << std::endl;
        getchar();
        exit(0);
    }
}

void znajdzFormeWTablicy(std::string str, double suma, double *kwota_inna) {
    for ( int i = 0; i < ILE_FORM_PLATNOSCI; i++ ) {
        if ((str) == FORMY_PLATNOSCI[i] ) {
            KWOTY_WPLACONE_PER_FORME_PLATNOSCI[i] = suma;
            if ( i > 1 ) { *kwota_inna = suma; }
        }
    }
}