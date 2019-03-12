//
// Created by Patryk on 14.04.2018.
//

#include "powiadomienia.h"
#include "constants.h"
#include "utilities.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

bool zalaczPojedynczaInstrukcje(std::string produkt, std::ofstream &mail, bool czy_napisane){
    std::cout<<"Zalaczam instrukcje produktu: "<<produkt<<std::endl;

    bool r = false;

    if(produkt!=""){
        std::fstream instrukcja;
        std::string nazwa_instrukcji = SCIEZKA_INSTRUKCJI + produkt + ".txt";
        instrukcja.open(nazwa_instrukcji.c_str());

        if(instrukcja.is_open()){
            r = true;
            if(!czy_napisane){
                mail << std::endl;
                mail << "Instrukcje monta¿u mebli znajduj¹ siê w za³¹cznikach."<<std::endl;
            }

            mail<<"--BOUNDARY"<<std::endl;
            mail<<"Content-Type: application/pdf; name=" + produkt + ".pdf"<<std::endl;
            mail<<"Content-Transfer-Encoding: base64"<<std::endl;
            mail<<"Content-Disposition: attachment; filename="+ produkt + ".pdf"<<std::endl;
            mail<<std::endl;

            std::string str;
            while(getline(instrukcja,str)){
                mail<<str<<std::endl;
            }
        }
        else{
            //szukamy w folderze i konwertujemy
            std::cout<<"Nie znalazlem takiej instrukcji!"<<std::endl;
        }
    }
    return r;
}

void zalaczWszystkieInstrukcje(std::ofstream &plik, KLIENT Janek){
    int i = -1;
    int licznik = 0;
    bool czy_napisane=false;
    while(i++<ILE_PRODUKTOW && Janek.produkty_kopia[i]!="zzzz"){
        licznik+= zalaczPojedynczaInstrukcje(Janek.produkty_kopia[i], plik, czy_napisane);
        if(licznik>0){
            czy_napisane=true;
        }
    }
    if(licznik==0){
        std::cout<<"Nie zalaczylem zadnej instrukcji"<<std::endl;
    }

}

void wypiszProduktyDoPliku(std::ofstream &plik, KLIENT Janek){
    int i = -1;
    while(i++<ILE_PRODUKTOW && Janek.produkty[i].kod!="zzzz"){
        plik << Janek.produkty[i].nazwa << "; " << Janek.produkty[i].kod << std::endl;
        plik << "Iloœæ: " << Janek.produkty[i].ilosc << std::endl;
        plik << "Wartoœæ: " << Janek.produkty[i].cena<< " z³" << std::endl;
    }
}

int  wypiszDane(std::ofstream &plik, std::string *tab){
    int i = 0;
    while(tab[i]!="" && i < 10){
        plik<<tab[i]<<std::endl;
        i++;
    }
    return i;
}

void wpiszSetup(std::ofstream &plik, KLIENT Janek){
    plik<<"To: "<< Janek.nazwisko << " <"<<Janek.mail<<">"<<std::endl;
    plik<<"Subject: Zamówienie "<<Janek.numer_zamowienia << std::endl;
    plik<<"From: Banach Wnetrza <"<<STANDARDOWY_MAIL<<">"<<std::endl;
    plik<<"MIME-Version: 1.0"<<std::endl;
    plik<<"Content-Type: multipart/mixed; boundary=\"BOUNDARY\""<<std::endl;
    plik<<std::endl;
    plik<<"--BOUNDARY"<<std::endl;
    plik<<"Content-Type: text/plain; charset=ansi"<<std::endl;
    plik<<"Content-Transfer-Encoding: quoted-printable"<<std::endl;
    plik<<std::endl;
}

void wpiszSetupFaktura(std::ofstream &plik, KLIENT Janek){
    plik<<"To: "<< Janek.nazwisko << " <"<<Janek.mail<<">"<<std::endl;
    plik<<"Subject: Faktura do zamówienia numer "<<Janek.numer_zamowienia << std::endl;
    plik<<"From: Banach Wnetrza <"<<STANDARDOWY_MAIL<<">"<<std::endl;
    plik<<"MIME-Version: 1.0"<<std::endl;
    plik<<"Content-Type: multipart/mixed; boundary=\"BOUNDARY\""<<std::endl;
    plik<<std::endl;
    plik<<"--BOUNDARY"<<std::endl;
    plik<<"Content-Type: text/plain; charset=ansi"<<std::endl;
    plik<<"Content-Transfer-Encoding: quoted-printable"<<std::endl;
    plik<<std::endl;
}

void wpiszTekst(std::ofstream &plik, KLIENT Janek){
    plik<<"Dziêkujemy za zakup naszych produktów."<<std::endl;

    plik<<"Numer Pañstwa zamówienia: "<<Janek.numer_zamowienia<<std::endl;

    plik<<"Przewidywany termin realizacji: "<<Janek.termin_dostawy<<std::endl;
    if(Janek.forma_dostawy==0){
        plik<<"Przewidywany termin realizacji: "<<Janek.termin_dostawy<<std::endl;
        plik<<"Odbiór osobisty"<<std::endl;
    }
    else {
        plik<<"Przewidywany termin wysy³ki: "<<Janek.termin_dostawy<<std::endl;
    }
    plik<<std::endl;

    plik<<"Zamówione produkty: "<<std::endl;
    wypiszProduktyDoPliku(plik, Janek);
    plik<<std::endl;

    plik<<"Kwota zamówienia: "<<Janek.kwota_brutto<<" z³"<<std::endl;
    plik<<"Wybrany sposób p³atnoœci: "<<Janek.forma_platnosci<<std::endl;
    plik<<std::endl;

    plik<<"Dane zamawiaj¹cego: "<<std::endl;

    //nie mam pojecia co to robi sorki
    int x = wypiszDane(plik, Janek.adres_klienta);
    plik<<std::endl;
    if(Janek.forma_dostawy==1){
        int i = 0;
        while(Janek.adres_dostawy[i]!="" && i < 10){
            i++;
        }
        if(i==x){
            plik<<"Adres dostawy: "<<std::endl;
            wypiszDane(plik, Janek.adres_dostawy);
        }
    }
    else if(Janek.forma_dostawy==0){
        plik<<"Odbiór osobisty"<<std::endl;
    }
}

void wpiszTekstFaktura(std::ofstream &plik, KLIENT Janek){

    plik<<"Dziêkujemy za zakup naszych produktów."<<std::endl;
    plik<<"Numer Pañstwa zamówienia: "<<Janek.numer_zamowienia<<std::endl;
    plik<<"Faktura znajduje siê w za³¹czniku."<<std::endl;
    plik<<std::endl;

    std::fstream faktura;
    std::string output2path = SCIEZKA_PLIKOW_DO_USUNIECIA + "output2.enc";
    faktura.open(output2path.c_str());

    plik<<"--BOUNDARY"<<std::endl;
    plik<<"Content-Type: application/pdf; name=faktura_" + Janek.numer_zamowienia + ".pdf"<<std::endl;
    plik<<"Content-Transfer-Encoding: base64"<<std::endl;
    plik<<"Content-Disposition: attachment; filename=faktura_" + Janek.numer_zamowienia + ".pdf"<<std::endl;
    plik<<std::endl;

    std::string str;
    while(getline(faktura ,str)){
        plik<<str<<std::endl;
    }
    plik<<"--BOUNDARY--"<<std::endl;

}

void przygotujTekstMailaZPowiadomieniem(KLIENT Janek, MAIL *Ania){
    std::ofstream tekst_maila;
    std::string nazwa_pliku = SCIEZKA_PLIKOW_DO_USUNIECIA +(Janek.nazwisko) + "_" + (Janek.numer_zamowienia) + ".mail";
    tekst_maila.open (nazwa_pliku.c_str());

    wpiszSetup(tekst_maila, Janek);
    wpiszTekst(tekst_maila, Janek);

    for(int i = 0; i < ILE_PRODUKTOW; i++){
        Janek.produkty_kopia[i]=Janek.produkty[i].kod;
    }
    //sortuje array produktow zeby nastepnie usunac duplikaty
    sort(Janek.produkty_kopia,Janek.produkty_kopia+ILE_PRODUKTOW);
    unique(Janek.produkty_kopia,Janek.produkty_kopia+ILE_PRODUKTOW);

    zalaczWszystkieInstrukcje(tekst_maila, Janek);
    tekst_maila<<"--BOUNDARY--"<<std::endl;
    tekst_maila.close();

    (*Ania).from=STANDARDOWY_MAIL;
    (*Ania).to=Janek.mail;
    (*Ania).wiadomosc=Janek.nazwisko + "_" + Janek.numer_zamowienia+".mail";;

    if(((*Ania).to).empty()){
        std::cout<<"Mail odbiorcy jest pusty. Sprawdz plik csv i uruchom program ponownie."<<std::endl;
        getchar();
        exit(0);
    }
}

void przygotujTekstMailaZPowiadomieniemdoHistorii(KLIENT Janek){
    std::ofstream tekst_maila_historii;
    std::string nazwa_historia = SCIEZKA_PLIKOW_DO_HISTORII + (Janek.nazwisko) + "_" + (Janek.numer_zamowienia)  + ".txt";
    tekst_maila_historii.open(nazwa_historia.c_str());

    wpiszSetup(tekst_maila_historii, Janek);
    wpiszTekst(tekst_maila_historii, Janek);
    tekst_maila_historii<<"--BOUNDARY--"<<std::endl;
    tekst_maila_historii.close();
}

void przygotujTekstMailaZFaktura(KLIENT Janek, MAIL *Ania){
    std::cout<<"Przygotowuje maila z faktura!"<<std::endl;

    std::string nazwa_pliku = SCIEZKA_PLIKOW_DO_USUNIECIA +(Janek.nazwisko) + "_" + (Janek.numer_zamowienia) + "FAKTURA.mail";

    std::ofstream tekst_maila;
    tekst_maila.open (nazwa_pliku.c_str());
    wpiszSetupFaktura(tekst_maila, Janek);
    wpiszTekstFaktura(tekst_maila, Janek);
    tekst_maila.close();

    //INICJALIZUJE INFORMACJE O MAILU
    (*Ania).from=STANDARDOWY_MAIL;
    (*Ania).to=Janek.mail;
    (*Ania).wiadomosc=Janek.nazwisko + "_" + Janek.numer_zamowienia+"FAKTURA.mail";;

    std::cout<<"Zalacze plik: "<<(*Ania).wiadomosc<<std::endl;

    if(((*Ania).to).empty()){
        std::cout<<"Mail odbiorcy jest pusty. Sprawdz plik csv i uruchom program ponownie."<<std::endl;
        getchar();
        exit(0);
    }
}

void wyslijPowiadomienie(KLIENT Janek) {
    MAIL Ania;
    przygotujTekstMailaZPowiadomieniem(Janek, &Ania);
    przygotujTekstMailaZPowiadomieniemdoHistorii(Janek);
    wyslijMail(Ania);
}

void wyslijFakture(KLIENT Janek){
    //tworze kopie faktury w base 64, w folderze plikow do usuniecia
    stworzKopieWBase64(SCIEZKA_FAKTURY_PDF, SCIEZKA_PLIKOW_DO_USUNIECIA);

    //w MAIL przechowywane sa informacje o odbiorcy etc
    MAIL Ania;

    przygotujTekstMailaZFaktura(Janek, &Ania);
    wyslijMail(Ania);
}

void zapiszKopieFaktury(KLIENT Janek) {
    //pod t¹ œcie¿k¹ zapiszê  kopiê faktury
    Janek.sciezka_do_kopii_faktury = SCIEZKA_KOPII_FAKTURY + Janek.numer_faktury +
                                              "_" + Janek.numer_zamowienia +  "_" +
                                              Janek.nazwisko + ".pdf";

    //kopiujê fakturê do odpowiedniego folderu
    kopiujPlik(SCIEZKA_FAKTURY_PDF, Janek.sciezka_do_kopii_faktury);
}