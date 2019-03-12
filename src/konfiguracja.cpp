//
// Created by Patryk on 13.04.2018.
//
#include "konfiguracja.h"
#include "utilities.h"
#include "paragon.h"
#include "powiadomienia.h"
#include "constants.h"
#include "mail.h"
#include "tabela.h"

#include <fstream>
#include <iostream>

void odczytajKonfiguracje(std::ifstream &plik, KONFIGURACJA *conf) {
    plik.open(SCIEZKA_DANE.c_str());
    std::cout<<"Odczytuje konfiguracje."<<std::endl;
    std::string temp;
    getline(plik, temp);
    usunSrednikiZeStringa(&temp);

    while ( !plik.eof()) {
        if ( temp == "mail" ) {
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
            (*conf).mail = (temp == "True");
        }
        if ( temp == "paragon" ) {
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
            (*conf).paragon = (temp == "True");
        }
        if ( temp == "faktura wysylka" ) {
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
            (*conf).faktura_wysylka = (temp == "True");
        }
        if ( temp == "faktura druk" ) {
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
            (*conf).faktura_druk = (temp == "True");
        }
        if ( temp == "ognik" ) {
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
            (*conf).ognik = (temp == "True");
        }
        if ( temp == "faktura zapis" ) {
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
            (*conf).faktura_zapis = (temp == "True");
        }
        getline(plik, temp);
        usunSrednikiZeStringa(&temp);
    }
    plik.close();
}

void wypiszWykonywaneProcedury(KONFIGURACJA conf) {
    if ( conf.mail ) std::cout << "Wysylam maila." << std::endl;
    else std::cout << "Nie wysylam maila." << std::endl;

    if ( conf.paragon ) std::cout << "Drukuje paragon." << std::endl;
    else std::cout << "Nie drukuje paragonu." << std::endl;

    if ( conf.faktura_wysylka ) std::cout << "Wysylam fakture." << std::endl;
    else std::cout << "Nie wysylam faktury." << std::endl;

    if ( conf.faktura_druk ) std::cout << "Drukuje fakture." << std::endl;
    else std::cout << "Nie drukuje faktury." << std::endl;

    if ( conf.faktura_zapis ) std::cout << "Tworze kopie faktury." << std::endl;
    else std::cout << "Nie tworze kopii faktury." << std::endl;

    if ( conf.ognik ) std::cout << "Zapisuje do tabeli." << std::endl;
    else std::cout << "Nie zapisuje do tabeli." << std::endl;
}

void wywolajProcedury(KONFIGURACJA conf, KLIENT Janek){
    if(conf.paragon) drukujParagon(Janek);
    if(conf.mail) wyslijPowiadomienie(Janek);
    if(conf.faktura_druk) drukujPlik(SCIEZKA_FAKTURY_PDF);
    if(conf.faktura_wysylka) wyslijFakture(Janek);
    if(conf.faktura_zapis) zapiszKopieFaktury(Janek);
    if(conf.ognik) zapiszDoTabeli(Janek, conf);
}
