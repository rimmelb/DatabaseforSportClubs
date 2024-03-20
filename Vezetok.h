#ifndef PROGRAM_VEZETOK_H
#define PROGRAM_VEZETOK_H

#include "Ember.h"
#include "String.h"
#include "memtrace.h"

class Vezetok : public Ember {
        String foglalkozas;
        String vegzettseg;
public:
        Vezetok(const String &n, size_t fiz, const String &fog, const String &veg);

        Vezetok(const Vezetok &a);

        void kiiro(std::ostream& os);

        void setVegzettseg(String const &a);

        Vezetok* clone() const;

        String getVegzettseg() const;

        String getFoglalkozas() const;

        ~Vezetok();
};



#endif //PROGRAM_VEZETOK_H
