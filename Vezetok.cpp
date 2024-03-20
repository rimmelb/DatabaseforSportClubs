#include "Vezetok.h"
#include "memtrace.h"


//A Vezetok osztaly konstruktora, ami meghivja az ososztalyanak konstruktorat is egyben
Vezetok::Vezetok(const String &n, size_t fiz, const String &fog, const String &veg) : Ember(n, fiz) {
    this->foglalkozas = fog;
    this->vegzettseg = veg;
}

//A Vezetok osztaly masolo konstruktora, ami meghivja az ososztalyanak masolo konstruktorat is egyben
Vezetok::Vezetok(const Vezetok &a) : Ember(a.getNev(), a.getFiz()) {
    vegzettseg = a.vegzettseg;
    foglalkozas = a.foglalkozas;
}

//A fuggveny lehetove teszi, hogy a Vezetok objektum adattagjai megjelenjenek a szabvanyos kimeneten
void Vezetok::kiiro(std::ostream &os) {
    os << getNev();
    os << " " << getFiz() << " ";
    os << foglalkozas;
    os << " ";
    os << vegzettseg;
    os << std::endl;
}

//Az osztaly destruktora
Vezetok::~Vezetok() {}


//A fuggveny segitsegevel beallithatjuk a Vezetok objektum vegzettseg adattagjat
void Vezetok::setVegzettseg(const String &a) {
    vegzettseg = a;
}

//A clone() fuggveny letrehoz az objektumbol egy dinamikus masolatot
Vezetok* Vezetok::clone() const {
    return new Vezetok(*this);
}

//A fuggveny segitsegevel visszaadhatjuk a Vezetok objektum vegzettseg adattagjat
String Vezetok::getVegzettseg() const {
    return vegzettseg;
}

//A fuggveny segitsegevel visszaadhatjuk a Vezetok objektum foglalkozas adattagjat
String Vezetok::getFoglalkozas() const {
    return foglalkozas;
}