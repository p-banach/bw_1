//
// Created by Patryk on 12.04.2018.
//

#ifndef KOMBAIIN_UTILITIES_H
#define KOMBAIIN_UTILITIES_H

#include <string>

#include "klient.h"
#include "constants.h"
#include "base64.h"

typedef std::basic_string<wchar_t> wstring;

std::string intToString(int a);

std::string wczytajPlikDoStringa(std::ifstream &in);

void usunSrednikiZeStringa(std::string *s);

double stringToDouble(std::string obiekt);

void wstawEndlCoNZnakow(std::ifstream &plikin, std::ofstream &plikout, int n);

void pominPuste(std::ifstream &plik, std::string *temp);

void Przypisanie(std::ifstream &plik, std::string *member, std::string *temp);

void odczytajDane(std::ifstream &plik, KLIENT *Janek);

void zamienCharANaB(std::string *str, char a, char b);

void kopiujPlik(std::string path_from, std::string path_to);

void stworzKopieWBase64(std::string from, std::string to);

void drukujPlik(std::string path);

std::string dataNaFormatRRRRMMDD(std::string data);

const std::string obecnaData();

void findAllFiles();

#endif //KOMBAIIN_UTILITIES_H
