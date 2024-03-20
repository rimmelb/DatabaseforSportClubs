#ifndef PROGRAM_ELLENORZOFUGGVENYEK_H
#define PROGRAM_ELLENORZOFUGGVENYEK_H
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include "Jatekosok.h"
#include "Vezetok.h"
#include "String.h"
#include "memtrace.h"

bool compare_szulev(Jatekosok* elso, Jatekosok* masodik);

bool compare_szerzodes_hatra(Jatekosok* elso, Jatekosok* masodik);

bool compare_fizetes(Jatekosok* elso, Jatekosok* masodik);

bool compare_mezszam(Jatekosok* elso, Jatekosok* masodik);

size_t ellenorzofuggveny(char* const &a, size_t hatar1, size_t hatar2, std::istream& is = std::cin);

size_t valasztasellenorzo();

size_t valasztasellenorzo_case1();

size_t kiadasellenorzo();

size_t bevetelellenorzo();

size_t convertToNumber(const char* s);

size_t szerzodes_ellenorzo(std::istream& is = std::cin);

size_t szuletesiev_ellenorzo(std::istream& is = std::cin);

size_t valasztasellenorzo_case2();

size_t valasztasellenorzo_case3();

size_t fizetesellenorzo(std::istream& is = std::cin);

String vegzettsegellenorzo(std::istream& is = std::cin);

bool is_valid(String const &a);

bool is_there_a_character(String const &a);

String get_valid_name(const char *szoveg, std::istream& is = std::cin);

String nevellenorzo(std::istream& is = std::cin);


#endif //PROGRAM_ELLENORZOFUGGVENYEK_H
