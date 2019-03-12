//
// Created by Patryk on 12.04.2018.
//

#ifndef KOMBAIIN_BASE64_H
#define KOMBAIIN_BASE64_H

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif //KOMBAIIN_BASE64_H
