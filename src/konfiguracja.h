//
// Created by Patryk on 13.04.2018.
//

#ifndef KOMBAIIN_KONFIGURACJA_H
#define KOMBAIIN_KONFIGURACJA_H

#include "klient.h"

struct KONFIGURACJA {
    bool mail;
    bool paragon;
    bool faktura_wysylka;
    bool faktura_zapis;
    bool faktura_druk;
    bool ognik;
};

void odczytajKonfiguracje(std::ifstream &plik, KONFIGURACJA *conf);

void wypiszWykonywaneProcedury(KONFIGURACJA conf);

void wywolajProcedury(KONFIGURACJA conf, KLIENT Janek);

#endif //KOMBAIIN_KONFIGURACJA_H
