//
// Created by Patryk on 12.04.2018.
//

#include "mail.h"

#include <string>
#include <windows.h> // WinExec i SW_HIDE

void wyslijMail(MAIL Ania){
    std::string command = dajPolecenieCURL(Ania);
    // tutaj zmieniam polecenie ze string na char*, bo WinExec cos takiego przyjmuje
    auto *cmd = new char[command.length() + 1];
    strcpy(cmd, command.c_str());
    // uruchamiam polecenie i czyszcze pamiec
    WinExec(cmd, SW_HIDE);
    delete[] cmd;
}

std::string dajPolecenieCURL(MAIL Ania) {
    return "curl * -v --mail-from " +(Ania.from)
    + " --mail-rcpt \""  + (Ania.to) + R"(" --ssl -u "*" -T ")"
                           + SCIEZKA_PLIKOW_DO_USUNIECIA + (Ania.wiadomosc) + "\" -k --anyauth ";
}
