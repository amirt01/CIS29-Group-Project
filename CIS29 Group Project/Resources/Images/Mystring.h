#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <string>
#include <algorithm>

class Mystring : public std::string
{
public:
    Mystring() {};
    ~Mystring() {};
    operator unsigned int();
    void tolower();
    void removePunctuation();
};

#endif