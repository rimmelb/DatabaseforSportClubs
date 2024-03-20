#ifndef PROGRAM_CSAPATTAG_H
#define PROGRAM_CSAPATTAG_H

#include "Ember.h"
#include "memtrace.h"


class Csapattag : public Ember {
    size_t csapatszam;
public:

    //A csapattag osztaly konstruktora, ami meghivja az ososztaly konstruktorat is egyben
    explicit Csapattag(String const &s = "", size_t fizet = 0, size_t csapatsz = 0) : Ember(s, fizet), csapatszam(csapatsz) {}

    Csapattag(const Csapattag &a);

    size_t getcsapatsz() const;

    void setcsapatsz(size_t a);

    virtual void kiiro(std::ostream& os) {}

    //A csapattag osztaly destruktora
    virtual ~Csapattag() override {}

    //Teljesen virtualis clone() fuggveny, melynek a csapattagbol szarmaztatott osztalyokban van fontos szerepe
    virtual Csapattag* clone() const = 0;
};


//Csapattagokat tartalmazo heterogen kollekcio megvalositasa
class Csapatok {
private:

    size_t darab;
    Csapattag **csapattag;          //Csapattagokat tartalmazo tomb

public:


    //A Csapatok osztaly konstruktora, ami a tomb meretet nullara inicializalja
    Csapatok() : darab(0), csapattag(nullptr) {}

    size_t getDarab() const;

    void add(Csapattag *a);

    Csapattag* operator[](size_t x) const;

    Csapattag** getCsapattag() const;

    void remove(Csapattag *a);

    void kiir(std::ostream& os = std::cout) const;

    ~Csapatok();
};




#endif //PROGRAM_CSAPATTAG_H
