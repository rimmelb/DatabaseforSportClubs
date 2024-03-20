#ifndef PROGRAM_EMBER_H
#define PROGRAM_EMBER_H

#include <iostream>
#include <cstring>
#include "String.h"
#include "memtrace.h"

class Ember {
    String nev;
    size_t fizetes;

public:

    explicit Ember(String const &s = "", size_t fizet = 0);

    Ember(const Ember &a);

    void setNev(String const &a);

    void setFiz(size_t a);

    Ember& operator=(const Ember &a);

    String getNev() const;

    size_t getFiz() const;

    virtual void kiiro(std::ostream& os) const;

    virtual ~Ember();
};


#endif //PROGRAM_EMBER_H
