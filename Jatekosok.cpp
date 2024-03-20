#include "Jatekosok.h"
#include "memtrace.h"


//A Jatekosok osztaly konstruktora, ami meghivja az ososztalyanak a konstruktorat is
Jatekosok::Jatekosok(String const &s, size_t fizet, size_t msz, size_t ev, size_t szer, size_t csapatszam) :
        Csapattag(s, fizet, csapatszam), mezszam(msz), szerzodes_hatra(szer), szulev(ev) {}

//A Jatekosok osztaly masolo konstruktora, ami meghivja az ososztalyanak a konstruktorat is
Jatekosok::Jatekosok(const Jatekosok &a) : Csapattag(a.getNev(), a.getFiz(), a.getcsapatsz()), mezszam(a.mezszam), szerzodes_hatra(a.szerzodes_hatra), szulev(a.szulev) {}

//A fuggveny visszaadja a Jatekosok objektum mezszam adattagjat
size_t Jatekosok::getMsz() const {
    return mezszam;
}

//A fuggveny visszaadja a Jatekosok objektum szerzodes_hatra adattagjat
size_t Jatekosok::getSzerzodes() const {
    return szerzodes_hatra;
}

//A fuggveny visszaadja a Jatekosok objektum szulev adattagjat
size_t Jatekosok::getSzulev() const {
    return szulev;
}

//A fuggveny segitsegevel felulirhatjuk a Jatekosok objektum szerzodes_hatra adattagjat
void Jatekosok::setSzer_hatra(size_t a) {
    szerzodes_hatra = a;
}

//A fuggveny visszaad egy dinamikus Csapattag masolatot egy Jatekosok objektumbol
Csapattag* Jatekosok::clone() const {
    auto *copy = new Jatekosok(*this);
    return copy;
}

//A fuggveny lehetove teszi, hogy a Jatekosok objektum adattagjai megjelenjenek a szabvanyos kimeneten
void Jatekosok::kiiro(std::ostream &os) {
    os << getNev();
    os << " " << getFiz() << " ";
    os << " " << mezszam << " " << szerzodes_hatra << " " << szulev << std::endl;
}

//A Jatekosok osztaly destruktora
Jatekosok::~Jatekosok() {}

