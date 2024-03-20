#ifndef PROGRAM_JATEKOSOK_H
#define PROGRAM_JATEKOSOK_H
#include "Csapattag.h"
#include "memtrace.h"


class Jatekosok : public Csapattag {
    size_t mezszam;
    size_t szerzodes_hatra;
    size_t szulev;
public:

    Jatekosok(String const &s, size_t fizet, size_t msz, size_t ev, size_t szer, size_t csapatszam);

    Jatekosok(Jatekosok const &a);

    size_t getMsz() const;

    size_t getSzerzodes() const;

    size_t getSzulev() const;

    void setSzer_hatra(size_t a);

    Csapattag* clone() const;

    void kiiro(std::ostream& os);

    ~Jatekosok();
};



#endif //PROGRAM_JATEKOSOK_H
