#ifndef PROGRAM_SZEMELYZET_H
#define PROGRAM_SZEMELYZET_H

#include "Csapattag.h"
#include <string>
#include "memtrace.h"

class Szemelyzet : public Csapattag {
    String szerepkor;
    String kepzettseg;

public:

    Szemelyzet(String const &nev, size_t fi, size_t csap, String const &foglal, String const &vegzett);

    Szemelyzet(Szemelyzet const &a);

    Csapattag* clone() const;

    String getvegzett() const;

    String getfoglal() const;

    void setKepzettseg(String const &a);

    void kiiro(std::ostream& os);

    ~Szemelyzet();
};


#endif //PROGRAM_SZEMELYZET_H
