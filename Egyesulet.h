#ifndef PROGRAM_EGYESULET_H
#define PROGRAM_EGYESULET_H

#include <limits>
#include <string>
#include <functional>
#include "Csapattag.h"
#include "Vezetok.h"
#include "Jatekosok.h"
#include "Szemelyzet.h"
#include "Ellenorzofuggvenyek.h"
#include "memtrace.h"

class Egyesulet {
    size_t bevetel;

    size_t kiadas;

    size_t kiad_egyeb;

    String** sportagak = nullptr;
    Csapatok** csapatok = nullptr;

    size_t jelenleg_csapatszam;
    size_t jelenleg_jatekosszam;

    Vezetok **vezettar = nullptr;
    size_t vezetokmeret;

public:

    ~Egyesulet();

    explicit Egyesulet(char const *fajl);

    void print_to_file(char const *fajl);

    void add_vezetok(Vezetok *a);

    void setJelenleg_Jatekosszam(size_t a);
    size_t getVezetokmeret() const;
    size_t getcsapatszam() const;

    void kiadasSet(size_t k);

    void bevetelSet(size_t b);

    size_t getBevetel() const;

    size_t getKiadas() const;

    Vezetok* getVezetok(size_t a) const;

    void print_out_vezetok() const;
    void details_of_egyesulet() const;
    void sort_vezetok_ABC() const;
    void sort_vezetok_fizetes() const;

    void print_out_sportagak() const;
    void print_selected_csapat(size_t i) const;

    size_t selected_csapat_jatekosok(size_t i);

    void print_selected_csapatszemelyzet(size_t i) const;
    void print_selected_csapatjatekosok(size_t i) const;

    void list_jatekosok_ev(size_t csapatindex, size_t ev) const;
    void list_jatekosok_szerhatra(size_t csapatindex, size_t ev) const;
    void list_jatekosok_fizetes(size_t csapatindex, size_t fizetes) const;

    void remove_Vezetok(size_t a, std::istream& is = std::cin);
    void remove_Szemelyzet_csapatbol(size_t i, size_t t, std::istream& is = std::cin);
    void remove_Jatekos_csapatbol(size_t i, size_t t);

    void add_jatekos(size_t csapatszam, Csapattag* a);
    bool mezszamellenorzo(size_t a, size_t mezszamos) const;
    void change_szerzodes(size_t csapatszam, size_t jatekosszam, size_t ujszerhossz);
    void change_fizetes(size_t csapatszam, size_t jatekosszam, size_t ujfizetes);
    void bubblesort_jatekosok(size_t csapatindex, std::function<bool(Jatekosok*, Jatekosok*)> compare);
    void delete_csapat(size_t csapatszam);
    void add_uj_csapat(Csapatok *a, String *b);

};

size_t delete_vezeto_check(Egyesulet const &a, std::istream& is = std::cin);
void kilistaz_vezetok(Egyesulet const &a, std::istream& is = std::cin);
void csapatkilistaz_ellenorzo(Egyesulet &a, std::istream& is = std::cin);
void adott_csapatbol_torles(Egyesulet &a, std::istream& is = std::cin);
void csapat_torles(Egyesulet &a, std::istream& is = std::cin);
void adott_csapathoz_hozzaadas(Egyesulet &a, std::istream& is = std::cin);
void adott_jatekossal_szerzodeshosszabbitas(Egyesulet &a, std::istream& is = std::cin);
void adott_csapatbol_listazas(Egyesulet &a, std::istream& is = std::cin);
void adott_csapatban_kereses(Egyesulet &a, std::istream& is = std::cin);
void csapat_hozzaadas(Egyesulet &a, std::istream& is = std::cin);
size_t adott_csapathoz_fuggvenyseged(Egyesulet &a, char* const &f, size_t hatar, std::istream& is = std::cin);
void adott_jatekos_fizetesvaltoztatas(Egyesulet &a, std::istream& is = std::cin);


#endif //PROGRAM_EGYESULET_H
