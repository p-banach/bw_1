//
// Created by Patryk on 12.04.2018.
//

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <chrono>
#include <experimental/filesystem>
#include "klient.h"
#include "utilities.h"
#include <Windows.h>

namespace fs = std::experimental::filesystem;

std::string intToString(int a) {
    std::ostringstream temp;
    temp << a;
    return temp.str();
}

void usunSrednikiZeStringa(std::string *s) {
    (*s).erase(remove((*s).begin(), (*s).end(), ';'), (*s).end());
}

std::string wczytajPlikDoStringa(std::ifstream &in) {
    //wczytuje caly plik do jednego stringa
    std::stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

double stringToDouble(std::string obiekt) {
    //przyjmuje string w formacie xxxxx.xx
    double wynik = strtod(obiekt.c_str(), NULL);
    return wynik;
}

void wstawEndlCoNZnakow(std::ifstream &plikin, std::ofstream &plikout, int n) {
    //wprowadza endl co n znakow
    int i = 0;
    char singlecharacter;
    while ( plikin.get(singlecharacter)) {
        if ( i == n ) {
            plikout << std::endl;
            i = 0;
        }
        plikout << singlecharacter;
        i++;
    }
}

void pominPuste(std::ifstream &plik, std::string *temp) {
    if ( plik.is_open()) {
        getline(plik, *temp);
        usunSrednikiZeStringa(temp);
        while ( !plik.eof() && *temp == "" ) {
            getline(plik, *temp);
            usunSrednikiZeStringa(temp);
        }
    }
}
// okropne :/
void odczytajDane(std::ifstream &plik, KLIENT *Janek) {

    plik.open(SCIEZKA_DANE.c_str());

    if ( plik.is_open()) {
        std::string temp;
        getline(plik, temp);

        usunSrednikiZeStringa(&temp);

        while ( !plik.eof() && temp != POCZATEK_DANYCH ) {

            getline(plik, temp);
            usunSrednikiZeStringa(&temp);
        }

        pominPuste(plik, &temp);
        usunSrednikiZeStringa(&temp);

        int ktory_produkt = 0;
        int licznik = 0;

        for ( int i = 0; i < ILE_PRODUKTOW; i++ ) {
            (*Janek).produkty[i].kod = "zzzz";
        }

        while ( !plik.eof() && temp != KONIEC_DANYCH ) {

            // tak dlugo jak nie skonczy sie plik ini pobieram dane
            if ( temp == "nazwisko:" ) {
                Przypisanie(plik, &(*Janek).nazwisko, &temp);
                licznik++;
            } else if ( temp == "mail:" ) {
                Przypisanie(plik, &(*Janek).mail, &temp);
                licznik++;
            } else if ( temp == "data:" ) {
                Przypisanie(plik, &(*Janek).data, &temp);
                licznik++;
            } else if ( temp == "numer_zamowienia:" ) {
                Przypisanie(plik, &(*Janek).numer_zamowienia, &temp);
                licznik++;
            } else if ( temp.find("produkt") != std::string::npos ) {
                if ( temp.find('/') != std::string::npos ) {
                    int pomoc = temp.find('_') + 1;
                    temp.std::string::erase(0, pomoc);
                } else {
                    temp.std::string::erase(0, 7);
                }
                (*Janek).produkty[ktory_produkt++].kod = temp;

                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                (*Janek).produkty[ktory_produkt - 1].nazwa = temp;

                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                (*Janek).produkty[ktory_produkt - 1].cena = stringToDouble(temp);

                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                (*Janek).produkty[ktory_produkt - 1].ilosc = stringToDouble(temp);


                (*Janek).produkty[ktory_produkt - 1].cena_za_sztuke =
                        (*Janek).produkty[ktory_produkt - 1].cena / (*Janek).produkty[ktory_produkt - 1].ilosc;

                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);

                if ( temp.find(32) != std::string::npos ) {
                    int pomoc = temp.find(32) + 1;
                    temp.std::string::erase(0, pomoc);
                }
                (*Janek).produkty[ktory_produkt - 1].jednostka_sprzedazy = temp;

                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                (*Janek).produkty[ktory_produkt - 1].vat = temp;

                licznik++;
            } else if ( temp == "cena:" ) {
                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);

                (*Janek).kwota_brutto = stringToDouble(temp);
                licznik++;
            } else if ( temp == "kwota netto:" ) {
                Przypisanie(plik, &(*Janek).kwota_netto, &temp);
                licznik++;
            } else if ( temp == "kwota vat:" ) {
                Przypisanie(plik, &(*Janek).kwota_vat, &temp);
                licznik++;
            } else if ( temp == "termin dostawy:" ) {
                Przypisanie(plik, &(*Janek).termin_dostawy, &temp);
                licznik++;
            } else if ( temp == "termin wystawienia:" ) {
                Przypisanie(plik, &(*Janek).termin_wystawienia_dokumentu, &temp);
                licznik++;
            } else if ( temp == "telefon :" ) {
                Przypisanie(plik, &(*Janek).telefon, &temp);
                licznik++;
            } else if ( temp == "termin platnosci:" ) {
                Przypisanie(plik, &(*Janek).termin_platnosci, &temp);
                licznik++;
            } else if ( temp == "forma platnosci:" ) {
                Przypisanie(plik, &(*Janek).forma_platnosci, &temp);
                licznik++;
            } else if ( temp == "numer faktury:" ) {
                Przypisanie(plik, &(*Janek).numer_faktury, &temp);
                zamienCharANaB(&(*Janek).numer_faktury, '/', '_');
                licznik++;
            } else if ( temp == "dane zamawiajacego:" ) {
                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                (*Janek).adres_klienta[0] = temp;
                int i = 0;
                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                while ( !plik.eof() && temp != "koniec danych" && i < 9 ) {
                    (*Janek).adres_klienta[++i] = temp;
                    pominPuste(plik, &temp);
                    usunSrednikiZeStringa(&temp);
                }
                licznik++;
            } else if ( temp == "dane dostawy:" ) {
                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                (*Janek).adres_dostawy[0] = temp;
                int i = 0;
                pominPuste(plik, &temp);
                usunSrednikiZeStringa(&temp);
                while ( !plik.eof() && temp != "koniec danych" && i < 9 ) {
                    (*Janek).adres_dostawy[++i] = temp;
                    pominPuste(plik, &temp);
                    usunSrednikiZeStringa(&temp);
                }
                licznik++;
            } else if ( temp == "nazwa zamowienia:" ) {
                if ( temp.find("ODBIOR") != std::string::npos ) {
                    (*Janek).forma_dostawy = 0;
                } else {
                    (*Janek).forma_dostawy = 1;
                }
                licznik++;
            }
            pominPuste(plik, &temp);
            usunSrednikiZeStringa(&temp);
        }
        plik.close();
    } else {
        std::cout << "Nie udalo sie otworzyc pliku plik.csv. Upewnij sie ze znajduje sie w folderze." << std::endl;
        getchar();
        exit(0);
    }
}

void Przypisanie(std::ifstream &plik, std::string *member, std::string *temp) {
    // member to jakis czlonek struktury
    pominPuste(plik, temp);
    usunSrednikiZeStringa(temp);
    *member = *temp;
}

void zamienCharANaB(std::string *str, char a, char b) {
    if ((*str).find(a) != std::string::npos ) {
        (*str)[(*str).find(a)] = b;
    }
}

void kopiujPlik(std::string path_from, std::string path_to) {
    std::ifstream src(path_from.c_str(), std::ios::binary);
    std::ofstream dst(path_to.c_str(), std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();
}

void stworzKopieWBase64(std::string from, std::string to) {

    // otwieram plik zeby pobrac z niego zawartosc
    std::ifstream plik;
    plik.open(from.c_str(), std::ios_base::in | std::ios_base::binary);

    // otwieram plik do ktorego go skopiuje
    std::ofstream kopia_pliku;
    std::string sciezka_do_kopii_pliku = to + "output1.enc";
    kopia_pliku.open(sciezka_do_kopii_pliku.c_str(), std::ios::trunc);

    // wczytuje plik do stringa i go zamykam
    std::string file = wczytajPlikDoStringa(plik);
    plik.close();

    // przepisuje zakodowany plik do pliku kopii i ja zamykam
    std::string file_encoded = base64_encode(reinterpret_cast<const unsigned char *>(file.c_str()), file.length());
    kopia_pliku << file_encoded;
    kopia_pliku.close();

    // otwieram pierwszy plik
    // tworze drugi, gdzie przepisuje pierwszy
    // wstawiajac breakline co n znakow
    std::ifstream output1a;
    output1a.open(sciezka_do_kopii_pliku.c_str());

    std::ofstream output2;
    std::string output2path = to + "output2.enc";
    output2.open(output2path.c_str(), std::ios::trunc);

    wstawEndlCoNZnakow(output1a, output2, 76);

    output1a.close();
    output2.close();
}

void drukujPlik(std::string path) {
    std::cout << "DRUKUJE MAN" << std::endl;
    std::string command = SCIEZKA_SUMATRY + path + "\" ";
    // tutaj zmieniam polecenie ze string na char*, bo WinExec cos takiego przyjmuje
    auto *cmd = new char[command.length() + 1];
    strcpy(cmd, command.c_str());
    // uruchamiam polecenie i czyszcze pamiec
    std::cout << cmd << std::endl;

    WinExec(cmd, SW_HIDE);
    delete[] cmd;
}

std::string dataNaFormatRRRRMMDD(std::string data) {
    //przyjmuje date w formacie DDMMRRRR
    std::string wynik;
    wynik += data.substr(6, 10);
    wynik += data.substr(2, 4);
    wynik += data.substr(0, 2);
    return wynik;
}

const std::string obecnaData() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y.%m.%d", &tstruct);

    return buf;
}