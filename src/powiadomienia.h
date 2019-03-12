//
// Created by Patryk on 14.04.2018.
//

#ifndef KOMBAIIN_POWIADOMIENIA_H
#define KOMBAIIN_POWIADOMIENIA_H

#include <string>

#include "klient.h"
#include "mail.h"


bool zalaczPojedynczaInstrukcje(std::string produkt, std::ofstream &mail, bool czy_napisane);

void zalaczWszystkieInstrukcje(std::ofstream &plik, KLIENT Janek);

void wypiszProduktyDoPliku(std::ofstream &plik, KLIENT Janek);

int wypiszDane(std::ofstream &plik, std::string *tab);

void wpiszSetup(std::ofstream &plik, KLIENT Janek);

void wpiszSetupFaktura(std::ofstream &plik, KLIENT Janek);

void wpiszTekst(std::ofstream &plik, KLIENT Janek);

void wpiszTekstFaktura(std::ofstream &plik, KLIENT Janek);

void przygotujTekstMailaZPowiadomieniem(KLIENT Janek, MAIL *Ania);

void przygotujTekstMailaZPowiadomieniemdoHistorii(KLIENT Janek);

void przygotujTekstMailaZFaktura(KLIENT Janek, MAIL *Ania);

void wyslijPowiadomienie(KLIENT Janek);

void wyslijFakture(KLIENT Janek);

void zapiszKopieFaktury(KLIENT Janek);

#endif //KOMBAIIN_POWIADOMIENIA_H
