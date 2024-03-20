#include "Egyesulet.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <istream>
#include "memtrace.h"

//A destruktor felszabaditja az Egyesulet objektum mindharom tombjet ugy, hogy vegigmegy a tomb osszes elemen, majd a tombot is felszabaditja
Egyesulet::~Egyesulet() {

    for (size_t i = 0; i < vezetokmeret; ++i) {
        delete vezettar[i];
    }
    delete[] vezettar;

    for (size_t i = 0; i < jelenleg_csapatszam; ++i) {
        delete sportagak[i];
    }
    delete[] sportagak;

    for (size_t i = 0; i < jelenleg_csapatszam; ++i) {
        delete csapatok[i];
    }
    delete[] csapatok;
}

//A beolvaso fuggveny, mely feltolti adattal az egyesulet objektum privat adattagjait
Egyesulet::Egyesulet(char const *fajl) {

    //Ha nem sikerul a fajlmegnyitas, akkor errort dob
    std::ifstream file(fajl);
    if (!file.is_open()) {
        throw "Sikertelen fajlmegnyitas";
    }
    bevetel = 0;
    kiad_egyeb = 0;
    jelenleg_jatekosszam = 0;
    //Beolvassa a fajl elso sorat, ami a jelenlegi bevetelt tartalmazza, majd a stringet szamma alakitja
    std::string line;
    std::getline(file, line);
    bevetel = std::stoi(line);
    //Beolvassa a fajl masodik sorat, ami az emberek fizetesen kivuli kiadast tartalmazza, majd a stringet szamma alakitja
    std::getline(file, line);
    kiad_egyeb = std::stoi(line);

    //Beolvassa a fajl harmadik sorat, ami a jelenlegi csapatok szamat tartalmazza, majd a stringet szamma alakitja
    std::getline(file, line);
    jelenleg_csapatszam = std::stoi(line);

    //Megtortenik a jelenlegi sportagak beolvasasa
    sportagak = new String*[jelenleg_csapatszam];
    //Beolvasasra kerul a jelenlegi sportagak nevei
    char sor[1000];
    file.getline(sor, 1000);
    size_t g = jelenleg_csapatszam;

    //Mivel a sportagak nevei ';'-vel vannak elvalasztva, igy a sor strtok segitsegevel feldarabolasra kerul
    char *sztringek[g];
    char *sztring;
    sztring = strtok(sor, ";");


    for(size_t i = 0; sztring  != nullptr; i++) {
        sztringek[i] = sztring;
        sztring = strtok(nullptr, ";");
    }

    //A *sztringek megfelelo elemeibol Stringet hoz letre, majd azt a korabban mar lefoglalt sportagak tombbe tarolja el
    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        sportagak[i] = new String(sztringek[i]);
    }


    vezetokmeret = 0;
    kiadas = 0;

    //Beolvassa a vezetoket hasonlo modszerrel, mint a sportagakat, de itt soronkent egy vezeto adatai talalhatoak meg
    while (file.getline(sor, 1000) && sor[0] != '#') {

        char *szovegek[4];
        char *szoveg;
        szoveg = strtok(sor, ";");
        for(size_t i = 0; szoveg  != nullptr; i++) {
            szovegek[i] = szoveg;
            szoveg = strtok(nullptr, ";");
        }

        String a(szovegek[0]);
        String b(szovegek[1]);

        std::string pay(szovegek[2]);
        size_t fzt = std::stoi(pay);

        String c(szovegek[3]);
        //Meghivja a vezetok konstruktort, majd ennek a dinamikus masolatat atadja a fuggvenynek, ami azt elhelyezi a vezettar tombben
        Vezetok uj(a, fzt, b, c);
        add_vezetok(uj.clone());
        //A kiadashoz hozzaadja a vezetonek a fizeteset
        kiadas += fzt;
    }

    //A csapatok eltarolasahoz lefoglalja a memoriaban a csapatoknak a helyet, majd a tomb minden elemenek foglal helyet
    csapatok = new Csapatok*[jelenleg_csapatszam];
    for (size_t i = 0; i < jelenleg_csapatszam; i++) {
        csapatok[i] = new Csapatok();
    }

    //Beolvasasra kerulnek a csapatok
    for (size_t i = 0; i < jelenleg_csapatszam; i++) {
        //Eloszor a csapathoz tartozo szemelyzet kerul beolvasasra hasonlo logikaval, mint a vezetok korabban
        while (file.getline(sor, 1000) && sor[0] != '#') {

            char *szovegek[5];
            char *szoveg;
            szoveg = strtok(sor, ";");

            for(size_t x = 0; szoveg!=nullptr; x++) {
                szovegek[x] = szoveg;
                szoveg = strtok(nullptr, ";");
            }

            std::string csapatsz(szovegek[0]);
            size_t csapatszam = std::stoi(csapatsz);

            String a(szovegek[1]);
            String b(szovegek[2]);

            std::string fizetseg(szovegek[3]);

            size_t fiz = std::stoi(fizetseg);

            String c(szovegek[4]);

            Szemelyzet uj(a, fiz, csapatszam, b, c);

            kiadas+=fiz;
            //A Szemelyzet objektumnak a Csapattag* tipusu dinamikus masolatat adja at
            csapatok[i]->add(uj.clone());
        }

        //A csapathoz tartozo szemelyzet utan a csapathoz tartozo jatekosok objektumok kerulnek beolvasasra
        while (file.getline(sor, 1000) && sor[0] != '#') {

            char *szovegek[6];
            char *szoveg;
            szoveg = strtok(sor, ";");

            for(size_t x = 0; szoveg != nullptr; x++) {
                szovegek[x] = szoveg;
                szoveg = strtok(nullptr, ";");
            }

            std::string csapatsz(szovegek[0]);
            size_t cssz = std::stoi(csapatsz);
            String a(szovegek[1]);

            std::string evszam(szovegek[2]);
            size_t ev = std::stoi(evszam);

            std::string mezsz(szovegek[3]);
            size_t mesz = std::stoi(mezsz);

            std::string fiz(szovegek[4]);
            size_t fzt = std::stoi(fiz);

            std::string szhatra(szovegek[5]);
            size_t szer_hatra = std::stoi(szhatra);
            //Ugyanaz tortenik, mint a Szemelyzet objektumok eseteben
            Jatekosok uj(a, fzt, mesz, ev, szer_hatra, cssz);

            kiadas += fzt;
            jelenleg_jatekosszam++;
            csapatok[i]->add(uj.clone());
        }
    }
    //hozzaadja a kiadashoz (emberek fizetese) az egyeb kiadasokat
    kiadas += kiad_egyeb;
    //Bezarja a fajlt
    file.close();
}

//A fuggveny az esetlegesen megvaltozott egyesulet objektumnak az adatait visszairja a fileba, azaz felulirja a korabban beolvasott adatokat
void Egyesulet::print_to_file(const char *fajl) {
    //Ha nem sikerul a fajlmegnyitas, akkor errort dob
    std::ofstream file(fajl);
    if(!file) {
        throw "Sikertelen fajlmegnyitas";
    }
    //Stringge alakitja az egyesulet size_t tipusu privat adattagjait, majd beirja a fileba
    std::string bev = std::to_string(bevetel);
    std::string kiad_e = std::to_string(kiad_egyeb);
    std::string csapatszam = std::to_string(jelenleg_csapatszam);

    file << bev << std::endl << kiad_e << std::endl << csapatszam << std::endl;

    //Egyszerubbe teszi a fajlbairast, ha a ';' és a '#' String objektumokka valnak, hiszen igy lancolhato
    String a(";"), b("#");

    //A sportagak nevei kerulnek fajlba irasra
    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        file << sportagak[i]->c_str();

        //Utolso utan ne tegyen ';'-t
        if(i + 1 != jelenleg_csapatszam) {
            file << a;
        }
    }
    file << std::endl;

    //A vezetok fajlba irasa
    for(size_t i = 0; i < vezetokmeret; i++) {
        //A vezetok objektumok fizetes adattagjat stringge alakitja
        std::string fiz = std::to_string(vezettar[i]->getFiz());

        file << vezettar[i]->getNev() << a << vezettar[i]->getFoglalkozas() << a << fiz << a << vezettar[i]->getVegzettseg() << std::endl;
    }
    //Elhelyez egy hashtaget, mellyel jelzi, hogy vege a vezetok objektumoknak
    file << b << std::endl;

    //Fajlba irasra kerulnek a csapatok
    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        //Mivel csapatonkent ot szemelyzet objektum van, igy 5-ig megy a ciklus
        for(size_t x = 0; x < 5; x++) {
            //Visszaalakitja a korabban letrehozott dinamikus masolatot a szarmaztatott osztaly objektumava
            auto *uj =  dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[x]);
            //Megtortenik a fajlba irasa a szemelyzet objektumnak
            std::string csapatsz = std::to_string(uj->getcsapatsz());
            std::string fizetseg = std::to_string(uj->getFiz());

            file << csapatsz << a << uj->getNev() << a << uj->getfoglal() << a << fizetseg << a << uj->getvegzett() << std::endl;
        }
        //A Szemelyzet utan egy ujabb hashtag, ezzel jelezve, hogy ennyi volt a szemelyzet objektumokbol
        file << b << std::endl;

        for(size_t z = 5; z < csapatok[i]->getDarab(); z++) {

            //Hasonlo logika menten tortenik meg a jatekosok objektumok adatainak a fajlba irasa, mint a szemelyzet objektumok fajlba irasa
            auto *uj =  dynamic_cast<Jatekosok*>(csapatok[i]->getCsapattag()[z]);

            std::string csapatsz = std::to_string(uj->getcsapatsz());
            std::string fizu = std::to_string(uj->getFiz());
            std::string ev = std::to_string(uj->getSzulev());
            std::string msz = std::to_string(uj->getMsz());
            std::string ev_hatra = std::to_string(uj->getSzerzodes());

            file << csapatsz << a << uj->getNev() << a << ev << a << msz << a << fizu << a << ev_hatra;

            //Ha eljut az utolso csapatok tombelemenek az utolso jatekosok objektumaig, akkor ne tegyen meg egy entert
            if(i+1 != jelenleg_csapatszam || z+1 != csapatok[i]->getDarab())
            file << std::endl;
        }
        //Ha eljut az utolso csapatokig, akkor az utolso csapat utan ne tegyen hashtaget, kulonben igen
        if(i+1 != jelenleg_csapatszam) {
            file << b << std::endl;
        }
    }
}

//Hozzaad egy vezetok objektumot a vezettarhoz
void Egyesulet::add_vezetok(Vezetok *a) {
    auto **tmp = new Vezetok*[this->vezetokmeret+1];
    for (size_t i = 0; i < vezetokmeret; i++) {
        tmp[i] = vezettar[i];
    }
    tmp[vezetokmeret++] = a;
    delete[] vezettar;
    vezettar = tmp;
}

//Be lehet allitani az egyesulet objektum jelenleg_jatekosszam adattagjat
void Egyesulet::setJelenleg_Jatekosszam(size_t a) {
    jelenleg_jatekosszam+=a;
}

//A fuggveny visszaadja az egyesulet objektumhoz tartozo vezettar tombnek a jelenlegi meretet
size_t Egyesulet::getVezetokmeret() const {
    return vezetokmeret;
}

//A fuggveny visszaadja az egyesulet objektumhoz tartozo jelenleg_csapatszam adattagot
size_t Egyesulet::getcsapatszam() const {
    return jelenleg_csapatszam;
}

//A fuggvennyel megvaltoztathatjuk az egyesulet objektumhoz tartozo kiad_egyeb adattag erteket
void Egyesulet::kiadasSet(size_t k) {
    kiad_egyeb += k;
}

//A fuggvennyel megvaltoztathatjuk az egyesulet objektumhoz tartozo bevetel adattag erteket
void Egyesulet::bevetelSet(size_t b) {
    bevetel+=b;
}

//A fuggveny segitsegevel megkaphatjuk az egyesulet objektum bevetel adattagjat
size_t Egyesulet::getBevetel() const {
    return bevetel;
}

//A fuggveny segitsegevel megkaphatjuk az egyesulet objektum kiad_egyeb adattagjat
size_t Egyesulet::getKiadas() const {
    return kiad_egyeb;
}

//A fuggveny segitsegevel megkaphatjuk a vezettar egyik vezetok objektumat
Vezetok* Egyesulet::getVezetok(size_t a) const {
    return vezettar[a];
}

//A fuggveny segitsegevel kiirhatjuk a vezettar tomb vezetok objektumainak az adattagjait ugy, hogy a fuggveny objektumonkent meghivja az objektumok kiiro fuggvenyet
void Egyesulet::print_out_vezetok() const{
    for(size_t i= 0; i < vezetokmeret; i++) {
        std::cout << i+1 << " ";
        vezettar[i]->kiiro(std::cout);
    }
}

//A fuggveny kiirja a szabvanyos kimenetre az egyesulet objektumnak a legfontosabb adattagjait
void Egyesulet::details_of_egyesulet() const {
    size_t kiad = kiadas + kiad_egyeb;
    std::cout << "Osszbevetel:" << bevetel << " Forint" << std::endl << "Osszkiadas : " << kiad << " Forint" << std::endl;
    std::cout << "Csapatok szama : " << jelenleg_csapatszam << std::endl << "Jatekosok szama: " << jelenleg_jatekosszam << std::endl;
}

//A fuggveny segitsegevel ABC sorrend szerint rendezhetjuk a vezetok objektumokat a nev adattagjuk szerint
void Egyesulet::sort_vezetok_ABC() const {
    //Elmenti az eredeti sorrendet egy vector taroloba
    std::vector<Vezetok*> eredeti_sorrend;
    for (size_t i = 0; i < vezetokmeret; i++) {
        eredeti_sorrend.push_back(vezettar[i]);
    }
    //Vegrehajtja a bubblesortot
    for (size_t i = 0; i < vezetokmeret-1; i++) {
        for (size_t j = 0; j < vezetokmeret-i-1; j++) {
            if (vezettar[j]->getNev().compare(vezettar[j+1]->getNev()) > 0) {
                Vezetok* uj = vezettar[j];
                vezettar[j] = vezettar[j+1];
                vezettar[j+1] = uj;
            }}}
    //kiirja a vezettar tomb elemeit
    for(size_t i = 0; i < vezetokmeret; i++) {
        vezettar[i]->kiiro(std::cout);
    }
    //Visszakapja az eredeti sorrendet
    for (size_t i = 0; i < vezetokmeret; i++) {
        vezettar[i] = eredeti_sorrend[i];
    }
}

//A fuggveny segitsegevel a fizetesuk nagysaga szerint rendezhetjuk a vezetok objektumokat
//Ugyanazt csinalja, mint az elozo fuggveny csak fizetes szerint
void Egyesulet::sort_vezetok_fizetes() const {
    std::vector<Vezetok*> eredeti_sorrend;
    for (size_t i = 0; i < vezetokmeret; i++) {
        eredeti_sorrend.push_back(vezettar[i]);
    }
    for (size_t i = 0; i < vezetokmeret-1; i++) {
        for (size_t j = 0; j < vezetokmeret-i-1; j++) {
            if (vezettar[j]->getFiz() < vezettar[j+1]->getFiz()) {
                Vezetok* uj = vezettar[j];
                vezettar[j] = vezettar[j+1];
                vezettar[j+1] = uj;
            }}}

    for(size_t i = 0; i < vezetokmeret; i++) {
        vezettar[i]->kiiro(std::cout);
    }
    for (size_t i = 0; i < vezetokmeret; i++) {
        vezettar[i] = eredeti_sorrend[i];
    }
}

//A fuggveny kiirja a szabvanyos kimenetre az egyesulet objektum sportagak tombjenek minden elemet
void Egyesulet::print_out_sportagak() const {
    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        std::cout << i+1 << " "<< sportagak[i]->c_str() << std::endl;
    }
}

//A fuggveny meghivja a parameterek altal meghatarozott csapatok tombnek az elemenek a kiiro fuggvenyet = megfelelo csapatnak az osszes objektuma kiirasra kerul
void Egyesulet::print_selected_csapat(size_t i) const {
    csapatok[i]->kiir();
}

//A fuggveny megadja, hogy a parameter altal kivant csapatban hany darab jatekosok objektum van
size_t Egyesulet::selected_csapat_jatekosok(size_t i) {
    size_t z = 0;
    for(size_t x = 0; x < csapatok[i]->getDarab(); x++) {
        //A dynamic_cast, amennyiben a csapatoknak a megadott objektuma nem a kivant objektum, akkor nullptr-t ad
        //Amennyiben a megadott csapattag valoban Jatekosok objektum, akkor a z valtozo erteke megno 1-el
        if(dynamic_cast<const Jatekosok*>(csapatok[i]->getCsapattag()[x]) != nullptr) {
            z++;
        }}
    return z;
}

//A fuggveny segitsegevel kiirasra kerulhetnek a parameter altal kivant csapatok tomb elemenek a szemelyzet adattagjai
void Egyesulet::print_selected_csapatszemelyzet(size_t i) const {
    size_t z = 1;
    for (size_t x = 0; x < csapatok[i]->getDarab(); x++) {
        //A dynamic_cast, amennyiben a csapatoknak a megadott objektuma nem a kivant objektum, akkor nullptr-t ad
        //Amennyiben a megadott csapattag valoban Szemelyzet objektum, akkor meghivodik a csapattagnak a kiiro fuggvenye
        if (dynamic_cast<const Szemelyzet*>(csapatok[i]->getCsapattag()[x]) != nullptr) {
            std::cout << z << " ";
            csapatok[i]->getCsapattag()[x]->kiiro(std::cout);
            z++;
        }}
}

//A fuggveny segitsegevel kiirasra kerulhetnek a parameter altal kivant csapatok tomb elemenek a Jatekosok adattagjai
void Egyesulet::print_selected_csapatjatekosok(size_t i) const{
    size_t z = 1;
    for(size_t x = 0; x < csapatok[i]->getDarab(); x++) {
        //A dynamic_cast, amennyiben a csapatoknak a megadott objektuma nem a kivant objektum, akkor nullptr-t ad
        //Amennyiben a megadott csapattag valoban Jatekosok objektum, akkor meghivodik a csapattagnak a kiiro fuggvenye
        if(dynamic_cast<const Jatekosok*>(csapatok[i]->getCsapattag()[x]) != nullptr) {
            std::cout << z << " ";
            csapatok[i]->getCsapattag()[x]->kiiro(std::cout);
            z++;
        }}
}

//A fuggveny kilistazza a parameter altal kivant csapatnak a jatekos adattagjait a masik parameter fuggvenyeben
void Egyesulet::list_jatekosok_ev(size_t csapatindex, size_t ev) const{
    //megszerzi a megfelelo csapatok tombelemnek a meretet
    size_t darab = csapatok[csapatindex]->getDarab();
    for (size_t i = 0; i < darab; i++) {
        //leellenorzi, hogy az adott elem biztosan Jatekosok adattag-e dynamic_casttel, tovabba, hogy megfelel-e az objektumhoz tartozo szulev adattag a parameternek
        if (dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i]) != nullptr && dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i])->getSzulev() > ev) {
            //Ha igen, akkor meghivja az objektum kiiro fuggvenyet
            dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i])->kiiro(std::cout);
        }
    }
}

//A fuggveny kilistazza a parameter altal kivant csapatnak a jatekos adattagjait a masik parameter fuggvenyeben
void Egyesulet::list_jatekosok_szerhatra(size_t csapatindex, size_t ev) const{
    //megszerzi a megfelelo csapatok tombelemnek a meretet
    size_t darab = csapatok[csapatindex]->getDarab();
    for (size_t i = 0; i < darab; i++) {
        //leellenorzi, hogy az adott elem biztosan Jatekosok adattag-e dynamic_casttel, tovabba, hogy megfelel-e az objektumhoz tartozo szerzodes_hatra adattag a parameternek
        if (dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i]) &&
            dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i])->getSzerzodes() > ev) {
            //Ha igen, akkor meghivja az objektum kiiro fuggvenyet
            dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i])->kiiro(std::cout);
        }
    }
}

//A fuggveny kilistazza a parameter altal kivant csapatnak a jatekos adattagjait a masik parameter fuggvenyeben
void Egyesulet::list_jatekosok_fizetes(size_t csapatindex, size_t fizetes) const{
    //megszerzi a megfelelo csapatok tombelemnek a meretet
    size_t darab = csapatok[csapatindex]->getDarab();
    for (size_t i = 0; i < darab; i++) {
        //leellenorzi, hogy az adott elem biztosan Jatekosok adattag-e dynamic_casttel, tovabba, hogy megfelel-e az objektumhoz tartozo fizetes adattag a parameternek
        if (dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i]) &&
            dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i])->getFiz() > fizetes) {
            //Ha igen, akkor meghivja az objektum kiiro fuggvenyet
            dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[i])->kiiro(std::cout);
        }
    }
}

//A fuggveny az egyesulet objektum vezettar tombjebol a parameter altal kivalasztott objektumanak adattagjait felulirja
void Egyesulet::remove_Vezetok(size_t a, std::istream& is) {
    //Uj tomb foglalasa
    auto** tmp = new Vezetok * [vezetokmeret];
    size_t x = 0;
    for(size_t i = 0; i < vezetokmeret; i++) {
        if(i != a) {
            tmp[x] = vezettar[i];
            x++;
        }
        else {
            //Beolvasasra kerul a Vezetok objektumnak az uj neve a segedfuggveny segitsegevel es beallitasra kerul
            String uj_nev = nevellenorzo(is);
            vezettar[i]->setNev(uj_nev);
            kiadas = kiadas - vezettar[i]->getFiz();
            //Beolvasasra kerul a Vezetok objektumnak az uj fizetese a segedfuggveny segitsegevel es beallitasra kerul
            size_t uj_fizetes = fizetesellenorzo(is);
            vezettar[i]->setFiz(uj_fizetes);
            kiadas = kiadas + vezettar[i]->getFiz();
            //Beolvasasra kerul a Vezetok objektumnak az uj vegzettsege a segedfuggveny segitsegevel es beallitasra kerul
            String uj_vegzettseg = vegzettsegellenorzo(is);
            vezettar[i]->setVegzettseg(uj_vegzettseg);
            //A megvaltozott vezettar[i], azaz a kivalasztott Vezetok objektum is hozzaadodik az atmeneti tombhoz
            tmp[x] = vezettar[i];
            x++;
        }
    }
    //Torli, majd felulirja a vezettar tombot
    delete[] vezettar;
    vezettar = tmp;
}

//A fuggveny segitsegevel a kivalasztott csapatnak a parameter altal megadott Szemelyzet objektumanak az adattagjait tudjuk valtoztatni
void Egyesulet::remove_Szemelyzet_csapatbol(size_t i, size_t t, std::istream& is) {
    //Beolvasasra kerul a Szemelyzet objektum uj nev adattagja es beallitasra kerul
    String nev = nevellenorzo(is);
    //Vegig szukseges a dynamic_cast hasznalata, kulonben nem lehetne beallitani
    dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[t])->setNev(nev);

    //Beolvasasra kerul a Szemelyzet objektum uj fizetes adattagja es beallitasra kerul
    size_t fiz = fizetesellenorzo(is);

    //Az uj fizetes beallitasa elott a korabbi fizetest levonja a kiadasokbol es a beallitas utan hozzaadja az uj fizetest a kiadasokhoz
    size_t csokkenes = dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[t])->getFiz()*(-1);
    kiadasSet(csokkenes);
    dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[t])->setFiz(fiz);
    kiadasSet(dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[t])->getFiz());

    //Beolvasasra kerul a Szemelyzet objektum uj vegzettseg adattagja es beallitasra kerul
    String uj_veg = vegzettsegellenorzo(is);
    dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[t])->setKepzettseg(uj_veg);
}

//A fuggveny a parametereknek megfeleloen torli a kivalasztott csapattag objektumot a remove fuggveny meghivasaval
void Egyesulet::remove_Jatekos_csapatbol(size_t i, size_t t) {
    csapatok[i]->remove(csapatok[i]->getCsapattag()[t]);
}

//A fuggveny a parametereknek megfelelo csapatnak meghivja az add fuggvenyet, hogy az atadott csapattag objektum hozzaadodjon a kivalasztott tombhoz
void Egyesulet::add_jatekos(size_t csapatszam, Csapattag *a) {
    csapatok[csapatszam]->add(a);
}

//A fuggveny segitsegevel ellenorizhetjuk, hogy a kivalasztott csapatban van-e egy olyan mezszam, ami megegyezik a parameterkent atadott mezszamos valtozoval
bool Egyesulet::mezszamellenorzo(size_t a, size_t mezszamos) const{
    for(size_t i = 0; i < csapatok[a]->getDarab(); i++) {
        //Dynamic casttal visszaalakitjuk a megfelelo csapattagot Jatekosok objektumma - ha az nem Jatekosok objektum, akkor nullptr-t ad
        if(dynamic_cast<const Jatekosok*>(csapatok[a]->getCsapattag()[i]) != nullptr) {
            //Ha a Jatekosok objektum mezszam adattagja megegyezik a parameterkent kapott ertekkel, akkor return false
            if(dynamic_cast<Jatekosok*>(csapatok[a]->getCsapattag()[i])->getMsz() == mezszamos) {
                return false;
            }
        }
    }
    //Kulonben return true
    return true;
}

//A fuggveny segitsegevel meg tudjuk valtoztatni az egyik Jatekosok objektumnak a szerzodes_hatra adattagjat
void Egyesulet::change_szerzodes(size_t csapatszam, size_t jatekosszam, size_t ujszerhossz) {
    auto *uj = dynamic_cast<Jatekosok*>(csapatok[csapatszam]->getCsapattag()[jatekosszam]);
    uj->setSzer_hatra(ujszerhossz);
    csapatok[csapatszam]->getCsapattag()[jatekosszam] = uj->clone();
    delete uj;
}

//A fuggveny segitsegevel meg tudjuk valtoztatni az egyik Jatekosok objektumnak a fizetes adattagjat
void Egyesulet::change_fizetes(size_t csapatszam, size_t jatekosszam, size_t ujfizetes) {
    auto *uj = dynamic_cast<Jatekosok*>(csapatok[csapatszam]->getCsapattag()[jatekosszam]);
    kiadas = kiadas - uj->getFiz();
    uj->setFiz(ujfizetes);
    kiadas = kiadas + uj->getFiz();
    csapatok[csapatszam]->getCsapattag()[jatekosszam] = uj->clone();
    delete uj;
}

//A fuggveny a parameterkent atadott segedfuggvennyel rendezi a bubblesort algoritmus segitsegevel a Jatekosok objektumokat a tombon belul egy megfelelo szempont szerint
void Egyesulet::bubblesort_jatekosok(size_t csapatindex, std::function<bool(Jatekosok*, Jatekosok*)> compare) {

    size_t darab = csapatok[csapatindex]->getDarab();
    for (size_t i = 0; i < darab - 1; i++) {
        for (size_t j = 0; j < darab - 1; j++) {
            //Csak akkor tortenik meg a csere, ha mind a ket csapattag objektum a csapatok tombon belul valoban Jatekosok objektum, tehat a dynamic_cast nem ad nullptr-t
            //Es ha teljesul a segedfuggveny altal megadott feltetel
            if (dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[j]) != nullptr && dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[j + 1])!= nullptr
                &&
                compare(dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[j]), dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[j + 1]))) {

                //Megtortenik a helycsere ugy, hogy egy temporary pointerben eltaroljuk az eredeti j-edik adattagot, majd swappolunk
                auto *uj = dynamic_cast<Jatekosok*>(csapatok[csapatindex]->getCsapattag()[j]);
                csapatok[csapatindex]->getCsapattag()[j] = csapatok[csapatindex]->getCsapattag()[j + 1];
                csapatok[csapatindex]->getCsapattag()[j + 1] = uj->clone();

                //Vegen torli az uj pointert, kulonben szivargas lenne
                delete uj;
            }
        }
    }
    //Ezt kovetoen a mar rendezett Jatekosok objektumokat kiirja a megadott csapatbol a print_selected_csapatjatekosok fuggveny meghivasaval
    print_selected_csapatjatekosok(csapatindex);

}

//A fuggveny megvalositja az egyesulet objektumbol a parameter altal kivalasztott csapatok heterogen kollekcio kitorleset
void Egyesulet::delete_csapat(size_t csapatszam) {
    //Lefoglalasra kerul egy atmeneti tomb
    auto **tmp = new Csapatok *[jelenleg_csapatszam-1];
    size_t db = 0;
    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        //Amennyiben nem ez a kerdeses csapat
        if(i != csapatszam) {

            //A g valtozoba eltarolja a megfelelo csapatnak a meretet
            size_t g = csapatok[i]->getDarab();
            //a temporary tomb elemenek helyet foglal
            tmp[db] = new Csapatok();
            //Vegigmegy a csapatok egyik tombjenek osszes elemen
            for (size_t x = 0; x < g; x++) {

                //Amennyiben a kivalasztott objektum valojaban Szemelyzet objektum
                if(dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[x]) != nullptr) {
                    //Beallitja a program a csapatszamat (Ha egy csapatot torol, lehet, hogy egyel csokken a csapatszama
                    dynamic_cast<Szemelyzet*>(csapatok[i]->getCsapattag()[x])->setcsapatsz(db+1);
                    //Hozzaadja tmp[db] heterogen kollekciohoz
                    tmp[db]->add(dynamic_cast<Szemelyzet *>(csapatok[i]->getCsapattag()[x])->clone());
                }
                //Hasonlo az else if ag, de itt azt ellenorzi, hogy a kivalasztott objektum Jatekosok objektum-e
                else if(dynamic_cast<Jatekosok*>(csapatok[i]->getCsapattag()[x]) != nullptr) {

                    dynamic_cast<Jatekosok*>(csapatok[i]->getCsapattag()[x])->setcsapatsz(db+1);
                    tmp[db]->add(dynamic_cast<Jatekosok*>(csapatok[i]->getCsapattag()[x])->clone());
                }
            }
            db++;
        }
        //Amennyiben megtalalja a ciklus azt a csapatok heterogen kollekciot amit torolni akar
        else  {
            //A ciklus megvalositja
            for (size_t z = 0; z < csapatok[i]->getDarab(); z++) {
                //Csokkentjuk az kiadasokat = toroljuk a csapattagok fizeteset
                size_t csokkenes = csapatok[i]->getCsapattag()[z]->getFiz();
                kiadas = kiadas - csokkenes;
                //Csokkentjuk a jatekosszamot
                jelenleg_jatekosszam--;
            }
            //Mivel csapatonkent biztosan ot szemelyzet objektum van, igy hozzaadunk a jatekosszamhoz otot
            jelenleg_jatekosszam += 5;

            //A sportagak tombbol is torlesre kerul a kivalasztott csapathoz tartozo sportagnev
            //atmeneti tombot foglalunk
            auto **temporary = new String*[jelenleg_csapatszam-1];
            size_t hossz = 0;

            for(size_t z = 0; z < jelenleg_csapatszam; z++) {
                //Ha nem talalja meg, akkor foglal az uj tombnek neki helyet es meghivja a String osztaly konstruktorat
                if(z != csapatszam) {
                    temporary[hossz] = new String(sportagak[z]->c_str());
                    hossz++;
                }
            }
            //Torli a sportagak tombot, majd felulirja
            for(size_t t = 0; t < jelenleg_csapatszam; t++) {
                delete sportagak[t];
            }
            delete[] sportagak;
            sportagak = temporary;
        }
    }
    //Torli a csapatok tombot, majd felulirja
    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        delete csapatok[i];
    }
    delete[] csapatok;

    csapatok = tmp;
    //Csokkenti a csapatszamot
    jelenleg_csapatszam--;

    //A vezettar tombbol kitorli a csapathoz tartozo szakosztalyvezetot
    //lefoglal egy atmeneti tombot
    auto **atmeneti = new Vezetok *[vezetokmeret-1];
    size_t atmenetiIndex = 0;
    //A ciklus kihagyja azt az elemet, amit torolni szeretnenk
    for(size_t i = 0; i < vezetokmeret; i++) {
        //Azert 4+csapatszam, mert 4 fo fix a vezetok kozott
        if(i != 4 + csapatszam) {
            atmeneti[atmenetiIndex++] = new Vezetok(vezettar[i]->getNev(), vezettar[i]->getFiz(), vezettar[i]->getFoglalkozas(), vezettar[i]->getVegzettseg());
        }
        else {
            size_t a = vezettar[i]->getFiz();
            kiadas = kiadas - a;
        }
    }
    //Torli a vezettar tombot, majd felulirja
    for(size_t i = 0; i < vezetokmeret; i++) {
        delete vezettar[i];
    }
    delete[] vezettar;
    vezettar = atmeneti;
    vezetokmeret = atmenetiIndex;
}

//A tagfuggveny megvaltoztatja az egyesulet objektumhoz tartozo sportagak es csapatok tomboket - mindkettohoz egy uj objektumot ad hozza
void Egyesulet::add_uj_csapat(Csapatok *a, String *b) {
    //Temporary tomboket hoz letre, majd a korabbi adatokat atadja a temporary tomboknek
    auto **tmp = new Csapatok * [jelenleg_csapatszam+1];
    auto **temporary = new String *[jelenleg_csapatszam+1];

    for(size_t i = 0; i < jelenleg_csapatszam; i++) {
        tmp[i] = csapatok[i];
        temporary[i] = sportagak[i];
    }

    //Az uj adatokat atadja a temporary tomboknek, torli a korabbi adatokat, majd az uj temporary tombbel felulirja
    tmp[jelenleg_csapatszam++] = a;

    jelenleg_csapatszam--;
    temporary[jelenleg_csapatszam++] = b;

    delete[] csapatok;
    delete[] sportagak;

    csapatok = tmp;
    sportagak = temporary;
}

//A fuggveny segitsegevel le tudjuk ellenorizni, hogy biztosan jo vezetok objektumot akarunk-e felulirni
size_t delete_vezeto_check(Egyesulet const &a, std::istream& is) {
    char f[100] = "Melyik vezetosegi tagot szeretne torolni?\n";
    //Meghivja a vezettar tombot kiiro fuggvenyt
    a.print_out_vezetok();
    //Meghivja az univerzalis beolvaso fuggvenyt
    size_t szam = ellenorzofuggveny(f, 1, a.getVezetokmeret(), is);
    //szam - 1, mivel tombben nullatol indexelodnek az elemek
    return szam - 1;
}

//A fuggveny segitsegevel meg tudjuk hivatni valamelyik vezettar rendezo fuggvenyt
void kilistaz_vezetok(Egyesulet const &a, std::istream& is) {
    //Univerzalis beolvasofuggveny meghivasa, hogy biztosan jo legyen a bemenet
    char f[150] = "Kerem, adja meg, hogy milyen szempont szerint szeretne listazni!\n1 - ABC sorrend szerint\n 2 - fizetes szerint\n";
    size_t szam = ellenorzofuggveny(f, 1, 2, is);
    switch(szam) {
        //Amennyiben 1 volt a valasztas, akkor meghivja az ABC sorrend szerint rendezo fuggvenyt, majd a kiiro fuggvenyt
        case 1: {
            a.sort_vezetok_ABC();
        }
        break;
        //Amennyiben 2 volt a valasztas, akkor meghivja a fizetes szerint rendezo fuggvenyt, majd a kiiro fuggvenyt
        case 2: {
            a.sort_vezetok_fizetes();
        }
        break;
    }
}

//A fuggveny segitsegevel leellenorizhetjuk, hogy a felhasznalo jo bemenetet ad-e meg a csapat megtekintesenel
void csapatkilistaz_ellenorzo(Egyesulet &a, std::istream& is) {
    char f[50] = "Melyik csapatot szeretne megtekinteni?\n";
    size_t szam = adott_csapathoz_fuggvenyseged(a, f, 1, is);
    a.print_selected_csapat(szam);

}

//A fuggveny megvalositja, hogy az egyesulet objektum csapatok tombjenek egyik elemebol egy megadott objektumot tudjunk torolni vagy felulirni
void adott_csapatbol_torles(Egyesulet &a, std::istream& is) {

    //Leellenorzi a bemeneteket azzal, hogy meghivja a segedfuggvenyt
    char fd[100] = "Melyik csapat osszetetelet szeretne megvaltoztatni?\n";
    size_t szam = adott_csapathoz_fuggvenyseged(a, fd, 1, is);
    //Szinten leellenorzi, hogy biztosan jo-e a bemenet
    char f[100] = "Melyik csapatreszbol szeretne torolni?\n1 - Szemelyzet kozul\n2 - Jatekosok kozul\n";
    size_t x = ellenorzofuggveny(f, 1, 2, is);

    // g = 5, hiszen 5 szemelyzet objektum van egy csapatban
    size_t g = 5;
    if(x == 1) {
        char sz[100] = "Kit szeretne kitorolni?\n";
        //Kiiratja a megfelelo csapatnak a szemelyzet objektumait
        a.print_selected_csapatszemelyzet(szam);
        //Leellenorzi, hogy helyes-e a bemenet
        size_t v = ellenorzofuggveny(sz, 1, g, is);
        v--;
        //A kapott parametereket atadja a remove_szemelyzet_csapatbol fuggvenynek
        a.remove_Szemelyzet_csapatbol(szam, v, is);
        return;
    }
    //Az u valtozoba elmenti, hogy az adott csapatnak hany jatekosa van
    size_t u = a.selected_csapat_jatekosok(szam);

     if(x == 2) {
         //Ellenorzi, hogy egyaltalan van-e jatekos a csapatban - ha nincs akkor visszater
         if (u == 0) {
             std::cout << "Nem tud tobb jatekost kitorolni, hiszen a kivalasztott csapatnak nincs jatekosa jelenleg!\n";
             return;
         }
         char sz[100] = "Kit szeretne kitorolni?\n";
         //Kiiratja a megfelelo csapatnak a jatekosok objektumait
         a.print_selected_csapatjatekosok(szam);
         //Leellenorzi, hogy biztosan jo bemenetet adott-e meg
         size_t p = ellenorzofuggveny(sz, 1, u, is);
         //valtozot csokkenti egyel - tombben nullatol tortenik az indexeles
         p--;
        // o = szemelyzet objektumok szama + hanyadik jatekost akarjuk kitorolni
        size_t o = g+p;
        //Atadja a parametereket a fuggvenynek, ami majd torli a kivalasztott objektumot a tombbol
        a.remove_Jatekos_csapatbol(szam, o);
        //Mivel torol egy jatekost, ezert csokken a jatekosszam is
        a.setJelenleg_Jatekosszam(-1);
        return;
    }
}

//Ellenorzi, hogy a felhasznalo letezo csapatot akar-e torolni
void csapat_torles(Egyesulet &a, std::istream& is) {
    //Ha nincs jelenleg csapat, akkor visszater a fuggveny
    if(a.getcsapatszam() == 0) {
        std::cout << "Nem lehet csapatot torolni, hiszen mar mindegyik csapatot kitorolte!\n";
        return;
    }
    //Kulonben meghivja az ellenorzo fuggvenyt - felhasznalo letezo csapatot torol - e
    char f[50] = "Melyik csapatot szeretne torolni?\n";
    size_t csapatszam = adott_csapathoz_fuggvenyseged(a, f, 1, is);
    //Kapott szamot atadja parameterkent a csapat_torol tagfuggvenynek, ami megvalositja a csapat torleset
    a.delete_csapat(csapatszam);
}

//A fuggveny segitsegevel letrehozhato egy uj Jatekosok objektum
void adott_csapathoz_hozzaadas(Egyesulet &a, std::istream& is) {
    //Ellenorzi, hogy jo bemenet erkezett-e
    char f[100] = "Melyik csapathoz szeretne jatekost hozzaadni?\n";
    size_t szam = adott_csapathoz_fuggvenyseged(a, f, 1, is);
    //Bekeri a Jatekosok objektum nevet es fizeteset
    String nev = nevellenorzo(is);
    size_t fizetes = fizetesellenorzo(is);

    //Mezszamellenorzo - a do-while ciklusban megnezi, hogy letezik-e mar ilyen mezszam
    size_t mesz;
    do{
        std::cout << "Mezszam: ";
        while(!(is >> mesz)) {
            std::cout << "Helytelen bemenet! Probalja ujra!\n";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(!a.mezszamellenorzo(szam, mesz)) {
            std::cout << "Sajnos a mezszam mar foglalt!\n";
        }

    }while(!a.mezszamellenorzo(szam, mesz));

    //Beolvassa az uj Jatekosok objektum szerzodes_hatra es szulev adattagjait
    size_t szerzodes_hatra = szerzodes_ellenorzo(is);
    size_t szuletesi_ev = szuletesiev_ellenorzo(is);
    //Meghivja a Jatekosok osztaly konstruktorat, ezzel egy uj objektumot letrehozva
    Jatekosok uj(nev, fizetes, mesz, szuletesi_ev, szerzodes_hatra, szam);
    //Hozzaadja a megfelelo csapathoz a jatekost
    a.add_jatekos(szam, uj.clone());
}

//A fuggveny segitsegevel kivalaszthato egy adott Jatekosok objektum, melynek megvaltoztathato a szerzodes_hatra adattagja
void adott_jatekossal_szerzodeshosszabbitas(Egyesulet &a, std::istream& is) {
    //Bemenetellenorzes
    char f[100] = "Melyik csapatbol szeretne jatekossal hosszabbitani?\n";
    size_t szam = adott_csapathoz_fuggvenyseged(a, f, 1, is);

    //Csapatonkent ot darab Szemelyzet objektum talalhato
    size_t o = 5;
    //Az u valtozo elmenti a kivalasztott csapatban levo Jatekosok objektumok szamat
    size_t u = a.selected_csapat_jatekosok(szam);
    //Kiiratja a kivalasztott csapatban levo jatekosok objektumokat
    a.print_selected_csapatjatekosok(szam);
    std::cout << "\n";
    //Ellenorzofuggveny
    char d[100]= "Kivel szeretne hosszabbitani?\n";
    size_t p = ellenorzofuggveny(d, 1, u, is);
    //Tombben nullatol indexeles miatt a valtozo erteket egyel csokkenti
    p--;
    //Ujfent ellenorzes
    char fd[50] = "Hany ev legyen az uj szerzodeshossz?\n";
    size_t uj_hossz = ellenorzofuggveny(fd, 0, 10, is);

    //r valtozo = szemelyzet objektumok szama + melyik jatekosok objektumon akarunk valtoztatast vegrehajtani
    size_t r = o+p;
    //Meghivja a fuggvenyt, ami elvegzi a szerzodeshossz valtoztatast
    a.change_szerzodes(szam, r, uj_hossz);
}

//A fuggveny segitsegevel az inputra erkezo adatok fuggvenyeben kilistazhato a megadott csapat jatekosok objektumai tobb szempont szerint
void adott_csapatbol_listazas(Egyesulet &a, std::istream& is) {
    //Ellenorzofuggveny
    char f[100] = "Melyik csapatbol szeretne listazni?\n";
    size_t csapatszam = adott_csapathoz_fuggvenyseged(a, f, 1, is);

    //Ujfent bemenetellenorzes
    char fd[200] = "Milyen szempont szerint szeretne listazni?\n1 - szuletesi ev\n2 - szerzodesbol hatralevo ido\n3 - fizetes nagysaga alapjan\n4 - mezszam szerint\n";
    size_t szam = ellenorzofuggveny(fd, 0, 4, is);

    switch (szam) {
        //Ha 1 volt a valasztas, akkor szuletesi ev szerint lehet a kivalasztott csapatbol a jatekosok objektumokat sorba rendezni
        case 1: a.bubblesort_jatekosok(csapatszam, compare_szulev);
            break;
        //Ha 2 volt a valasztas, akkor a hatralevo szerzodes hossza szerint lehet a kivalasztott csapatbol a jatekosok objektumokat sorba rendezni
        case 2: a.bubblesort_jatekosok(csapatszam, compare_szerzodes_hatra);
            break;
        //Ha 3 volt a valasztas, akkor a fizetes nagysaga szerint lehet a kivalasztott csapatbol a jatekosok objektumokat sorba rendezni
        case 3: a.bubblesort_jatekosok(csapatszam, compare_fizetes);
            break;
        //Ha 4 volt a valasztas, akkor a mezszam szerint lehet a kivalasztott csapatbol a jatekosok objektumokat sorba rendezni
        case 4: a.bubblesort_jatekosok(csapatszam, compare_mezszam);
            break;
        default:
            // nem történt megfelelő választás, ebben az esetben nem szükséges tenni semmit
            break;
    }
}

//A fuggveny segitsegevel a bemenetrol erkezo adatok fuggvenyeben lehet az egyik csapatbol keresni a Jatekosok objektumok kozott
void adott_csapatban_kereses(Egyesulet &a, std::istream& is) {
    //Ellenorzofuggvenyek = megfelelo bemenet erkezik-e
    char fd[200] = "Melyik csapatban szeretne keresni?\n";
    size_t csapatszam = adott_csapathoz_fuggvenyseged(a, fd, 1, is);

    char fer[200] = "Milyen szempont szerint szeretne keresni?\n1 - szuletesi ev szerint\n2 - szerzodesbol hatralevo ido szerint\n3 - fizetes alapjan\n";
    size_t szempont = ellenorzofuggveny(fer, 1, 3, is);

    switch (szempont) {
        case 1:
        {
            //Ha 1 volt a valasztas, akkor a helyes bemenet megerkezese utan a program meghivja a tagfuggvenyt, mellyel a megadott evszamtol felfele kilistazza a Jatekosok objektumokat
            char f[50] = "Melyik evtol felfele listazza ki?\n";
            size_t ev_szerint = ellenorzofuggveny(f, 1960, 2010, is);
            a.list_jatekosok_ev(csapatszam, ev_szerint); //szuletesi evet megad es aszerint keres
            break;
        }
        case 2:
        {
            //Ha 2 volt a valasztas, akkor a helyes bemenet megerkezese utan a program meghivja a tagfuggvenyt, mellyel a megadott szerzodeshossztol felfele kilistazza a Jatekosok objektumokat
            char f[50] = "Hany ev legyen hatra a szerzodesekbol?\n";
            size_t szerhat = ellenorzofuggveny(f, 0, 10, is);
            a.list_jatekosok_szerhatra(csapatszam, szerhat); //szerzodesbol hatralevo ido megad es aszerint keres
            break;
        }
        case 3:
        {
            //Ha 2 volt a valasztas, akkor a helyes bemenet megerkezese utan a program meghivja a tagfuggvenyt, mellyel a megadott fizetes nagysagatol felfele kilistazza a Jatekosok objektumokat
            char f[50] = "Mennyi forinttol listazzam ki?\n";
            size_t hatar = ellenorzofuggveny(f, 0, 1000000000, is);
            a.list_jatekosok_fizetes(csapatszam, hatar); //fizetes szerint
            break;
        }
        default:
            // nem történt megfelelő választás, ebben az esetben nem szükséges tenni semmit
            break;
    }
}

//A fuggveny segitsegevel inicializalhato egy uj csapat tomb
void csapat_hozzaadas(Egyesulet &a, std::istream& is) {

    //Ellenorzi, hogy megfelelo e az uj sportagnev
    char f[100] = "Melyik sportagban szeretne csapatot inditani?\n";
    String sportagnev = get_valid_name(f, is);
    //Egy dinamikus pointert hoz neki letre
    auto *uj_sportagnev = new String(sportagnev);
    //Egy uj csapat tombnek foglal helyet
    auto *wer = new Csapatok();

    //5 szemelyzet objektum kell, hogy legyen a csapatban, ami 5 foglalkozast jelent
    auto *foglalkozasok = new String[5];
    foglalkozasok[0] = String("foedzo"), foglalkozasok[1] = String("eronleti edzo");
    foglalkozasok[2] = String("sportorvos"), foglalkozasok[3] = String("masszor");
    foglalkozasok[4] = String("gyogytornasz");

    //Eloszor a szakosztalyvezetot olvassa be, ami hozzaadodik a vezettar tombhoz
    std::cout << "Kerem adja meg a szakosztalyvezetot!\n";
    String szak_nev = nevellenorzo(is);
    String elvalaszto("-");
    String szak("szakosztalyvezeto");
    String szak_vezeto = sportagnev + elvalaszto + szak;
    size_t szak_fiz = fizetesellenorzo(is);
    String szak_vegzettseg = vegzettsegellenorzo(is);


    Vezetok uj(szak_nev, szak_fiz, szak_vezeto, szak_vegzettseg);
    a.add_vezetok(uj.clone());

    //Beolvassa az ot Szemelyzet objektumot, meghivja a beolvasott adatokkal a konstruktort es az objektum dinamikus masolatat adja at a segedfuggvenynek
    for(size_t i = 0; i < 5; i++) {
        std::cout << "Kerem adja meg a " << foglalkozasok[i].c_str() << "-t!\n" << std::endl;
        String nev = nevellenorzo(is);
        size_t fiz = fizetesellenorzo(is);
        String vegzettseg = vegzettsegellenorzo(is);

        Szemelyzet hozzaad(nev, fiz, a.getcsapatszam()+1, foglalkozasok[i], vegzettseg);
        wer->add(hozzaad.clone());
    }
    //Beolvassa az ot Jatekosok objektumot, meghivja a beolvasott adatokkal a konstruktort es az objektum dinamikus masolatat adja at a segedfuggvenynek
    for(size_t i = 0; i < 5; i++) {
        std::cout << "Kerem, adja meg az " << i+1 << ". jatekos adatait!\n";
        String nev = nevellenorzo(is);
        size_t fiz = fizetesellenorzo(is);
        size_t szulev = szuletesiev_ellenorzo(is);
        size_t mezsz = i+1;
        size_t szerz_hat = szerzodes_ellenorzo(is);
        size_t cssz = a.getcsapatszam()+1;
        Jatekosok hozzaad(nev, fiz, mezsz, szulev, szerz_hat, cssz);
        //Noveli a jelenlegi jatekosszamot is
        a.setJelenleg_Jatekosszam(1);
        wer->add(hozzaad.clone());
    }
    //Hozzaadja az uj csapatot es sportagnevet az egyesulet sportagak es csapatok tombjehez
    a.add_uj_csapat(wer, uj_sportagnev);
    delete[] foglalkozasok;
}

//A fuggveny letezese abbol az okbol adodik, hogy bar az ellenorzofuggvennyel is meg lehetne oldani a hasznalatat, de
//mivel tobb helyen is ki kell iratni a jelenlegi sportagakat, igy egyszerubb egy segedfuggvenyt letrehozni
size_t adott_csapathoz_fuggvenyseged(Egyesulet &a, char *const &f, size_t hatar, std::istream& is) {
    a.print_out_sportagak();
    size_t szam = ellenorzofuggveny(f, hatar, a.getcsapatszam(), is);
    //-1, mivel tombben nullatol indexelunk
    szam--;
    return szam;
}


//A fuggveny megegyezik az adott_jatekossal_szerzodeshosszabbitas fuggvennyel, de itt az adott csapatbol kivalasztott
//Jatekosok objektumnak a fizetes adattagjat valtoztatjuk meg
void adott_jatekos_fizetesvaltoztatas(Egyesulet &a, std::istream& is) {
    char f[100] = "Melyik csapatbol szeretne egy jatekos fizeteset megvaltoztatni?\n";
    size_t szam = adott_csapathoz_fuggvenyseged(a, f, 1, is);


    size_t o = 5; //szemelyzet objektumok szama csapatonkent
    size_t u = a.selected_csapat_jatekosok(szam);
    std::cout << "\n";
    a.print_selected_csapatjatekosok(szam);
    char d[100]="Kinek a fizeteset szeretne megvaltoztatni?\n";
    size_t p = ellenorzofuggveny(d, 1, u, is);
    p--;
    char fd[50] = "Mennyi legyen az uj fizetese?\n";
    size_t uj_fizet = ellenorzofuggveny(fd, 0, 100000000, is);

    size_t r = o+p;
    a.change_fizetes(szam, r, uj_fizet);
}