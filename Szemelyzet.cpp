#include "Szemelyzet.h"
#include "Csapattag.h"
#include "memtrace.h"


//A Szemelyzet osztaly konstruktora, ami meghivja az ososztalyainak a konstruktorat is
Szemelyzet::Szemelyzet(const String &nev, size_t fi, size_t csap, const String &foglal, const String &vegzett) : Csapattag(nev, fi, csap) {
    szerepkor = foglal;
    kepzettseg = vegzett;
}

//A Szemelyzet osztaly masolo konstruktora, ami meghivja az ososztalyainak a konstruktorat is
Szemelyzet::Szemelyzet(const Szemelyzet &a) : Csapattag(a.getNev(), a.getFiz(), a.getcsapatsz()) {
    szerepkor = a.szerepkor;
    kepzettseg = a.kepzettseg;
}

//A clone() fuggveny letrehoz egy dinamikus Csapattag masolatot egy Szemelyzet objektumbol
Csapattag *Szemelyzet::clone() const {
    auto *copy = new Szemelyzet(*this);
    return copy;
}

//A fuggveny segitsegevel megkaphatjuk egy Szemelyzet objektum kepzettseg adattagjat
String Szemelyzet::getvegzett() const {
    return kepzettseg;
}

//A fuggveny segitsegevel megkaphatjuk egy Szemelyzet objektum szerepkor adattagjat
String Szemelyzet::getfoglal() const {
    return szerepkor;
}

//A fuggveny segitsegevel megvaltoztathatjuk a Szemelyzet objektum kepzettseg adattagjat
void Szemelyzet::setKepzettseg(const String &a) {
    kepzettseg = a;
}

//A fuggveny segitsegevel a szabvanyos bemenetre irhatjuk ki a Szemelyzet objektum adattagjait
void Szemelyzet::kiiro(std::ostream &os) {
    os << getNev();
    os << " " << getFiz() << " ";
    os << szerepkor;
    os << " ";
    os << kepzettseg;
    os << std::endl;
}

//A Szemelyzet osztaly destruktora
Szemelyzet::~Szemelyzet() {}
