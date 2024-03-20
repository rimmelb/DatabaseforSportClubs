#include "Ember.h"
#include "memtrace.h"


//Az Ember osztaly konstruktora
Ember::Ember(const String &s, size_t fizet) {
    nev = s;
    fizetes = fizet;
}

//Az Ember osztaly masolo konstruktora
Ember::Ember(const Ember &a) {
    nev = a.nev;
    fizetes = a.fizetes;
}

//A fuggveny segitsegevel beallithatjuk az Ember nev adattagjat
void Ember::setNev(const String &a) {
    nev = a;
}

//A fuggveny segitsegevel beallithatjuk az Ember fizetes adattagjat
void Ember::setFiz(size_t a) {
    fizetes = a;
}

//A fuggveny segitsegevel visszaadhatjuk az Ember objektum nev adattagjat
String Ember::getNev() const {
    return nev;
}

//A fuggveny segitsegevel visszaadhatjuk az Ember objektum fizetes adattagjat
size_t Ember::getFiz() const {
    return fizetes;
}

//A fuggveny segitsegevel az Ember objektum atveheti egy masik Ember objektum adatait
Ember& Ember::operator=(const Ember &a) {
    if(this!=&a) {
        nev = a.nev;
        fizetes = a.fizetes;
    }
    return *this;
}

//A fuggveny segitsegevel megvalosul az Ember objektum adattagjainak szabvanyos kimeneten valo megjelenitese
void Ember::kiiro(std::ostream &os) const{
    os << nev;
    os << fizetes << std::endl;
}

//Az Ember fuggveny destruktora, ami virtualis, hiszen ososztaly
Ember::~Ember() {}

