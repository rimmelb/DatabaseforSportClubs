#include "Csapattag.h"
#include "memtrace.h"


//A fuggveny az objektum tombjehez hozzáad egy uj objektumot
void Csapatok::add(Csapattag *a) {
        auto **tmp = new Csapattag *[this->darab+1];

        for (size_t i = 0; i < darab; i++) {
            tmp[i] = csapattag[i];
        }
        tmp[darab++] = a;
        delete[] csapattag;
        csapattag = tmp;
    }


//A destruktorban meghivasra kerul a csapattag tomb elemeinek destruktora, tovabba torlodik maga a tomb is
Csapatok::~Csapatok() {
    for (size_t i = 0; i < darab; i++) {
        delete csapattag[i];
    }
    delete[] csapattag;
}

//A fuggveny lehetove teszi, hogy a parameterkent atadott csapattag torlodjon az adott tombbol
void Csapatok::remove(Csapattag *a) {
     auto** tmp = new Csapattag*[darab-1];
     size_t j = 0;
     for (size_t i = 0; i < darab; i++) {
         if (csapattag[i] != a) {
             tmp[j] = csapattag[i];
             j++;
         }
     }
     delete[] csapattag;
     csapattag = tmp;
     delete a;
     darab = j;
}

//A fuggveny meghivja a tomb elemeinek kiiro fuggvenyet, ezzel megvalositva, hogy a csapattag tomb osszes objektumanak osszes adatai megjelenjen a kimeneten
void Csapatok::kiir(std::ostream &os) const {
    for(size_t i = 0; i < darab; i++) {
        csapattag[i]->kiiro(os);
    }
}

//visszaadja az objektumhoz tartozo tomb meretet
size_t Csapatok::getDarab() const {
    return darab;
}
//Visszaad a tomb egy elemere mutato pointert
Csapattag *Csapatok::operator[](size_t x) const {
    return csapattag[x];
}

//Visszaadja az objektumhoz tartozo objektumokat tarolo tombot
Csapattag **Csapatok::getCsapattag() const {
    return csapattag;
}
//Visszaadja az objektum csapatszam adatat
size_t Csapattag::getcsapatsz() const {
    return csapatszam;
}
//A fuggveny segitsegevel beallithato a csapattag objektum csapatszam adata
void Csapattag::setcsapatsz(size_t a) {
    csapatszam = a;
}

//A csapattag osztaly masolo konstruktora, ami meghivja az ososztaly konstruktorat is egyben
Csapattag::Csapattag(const Csapattag &a) : Ember(a.getNev(), a.getFiz()), csapatszam(a.csapatszam) {}
