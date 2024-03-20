#ifndef PROGRAM_STRING_H
#define PROGRAM_STRING_H

#include <iostream>
#include <cstring>
#include "memtrace.h"


//A String osztaly egy segitosztaly, melynek objektumait hasznalom az std::string leheto legteljesebb helyettesitesere
class String {
        char *pData;
        size_t len;

public:

    String();
    String(char ch);
    String(const char *s1);
    String(const String& a);
    size_t size() const;
    const char* c_str() const;
    String& operator=(const String &a);
    char& operator[](size_t a);
    const char& operator[](size_t a) const;
    String operator+(const String& a) const;
    String operator+(char ch) const;
    ~String();
    int compare(String const &b);
    bool operator==(String const &a);
};

std::ostream& operator<<(std::ostream & os, String const &a);




#endif //PROGRAM_STRING_H

