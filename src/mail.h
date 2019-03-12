//
// Created by Patryk on 12.04.2018.
//

#ifndef KOMBAIIN_MAIL_H
#define KOMBAIIN_MAIL_H

#include "constants.h"

struct MAIL {
    std::string from;
    std::string to;
    std::string wiadomosc;
};

std::string dajPolecenieCURL(MAIL Ania);
void wyslijMail(MAIL Ania);


#endif //KOMBAIIN_MAIL_H
