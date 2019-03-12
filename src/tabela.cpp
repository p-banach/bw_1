//
// Created by Patryk on 15.04.2018.
//

#include "tabela.h"
#include "utilities.h"

#include <fstream>
#include <iostream>

void zapiszDoTabeli(KLIENT Janek, KONFIGURACJA conf) {
    std::ofstream tabela;
    tabela.open(SCIEZKA_PLIKU_EXCELA.c_str(), std::ios::out | std::ios::app);
    tabela << "\n";

    tabela << Janek.numer_zamowienia;
    tabela << ";";

    tabela << Janek.nazwisko;
    tabela << ";";

    if ( conf.faktura_zapis ) {
        tabela << "FAKTURA;";
        tabela << Janek.numer_faktury;
        tabela << ";";
        tabela << dataNaFormatRRRRMMDD(Janek.termin_wystawienia_dokumentu);
        tabela << ";";
    } else {
        tabela << ";;;";
    }

    if ( conf.paragon ) {
        tabela << "PARAGON;";
        tabela << Janek.numer_paragonu;
        tabela << ";";
        tabela << obecnaData();
        tabela << ";";
    } else {
        tabela << ";;;";
    }


    tabela << Janek.kwota_netto;
    tabela << ";";
    tabela << Janek.kwota_vat;
    tabela << ";";
    tabela << Janek.kwota_brutto;
    tabela << ";";

    tabela << Janek.forma_platnosci;
    tabela << ";";

    if(Janek.sciezka_do_kopii_faktury!=""){
        tabela << R"(=HYPERLINK(")";
        tabela << Janek.sciezka_do_kopii_faktury;
        tabela << R"("))";
    }

    tabela.close();
}