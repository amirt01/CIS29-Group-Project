#include "Mystring.h"

Mystring::operator unsigned int() {
    unsigned ret = 0;
    for (char c : *this)
        ret += c;
    return ret;
};

void Mystring::tolower() {
    std::transform(std::string::begin(),
        std::string::end(),
        std::string::begin(),
        [](unsigned char c) { return std::tolower(c); });
};

void Mystring::removePunctuation() {
    std::string::erase(std::remove_if(std::string::begin(),
        std::string::end(),
        ispunct),
        std::string::end());
};
