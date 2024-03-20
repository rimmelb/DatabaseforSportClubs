#include "String.h"
#include "memtrace.h"


//A parameter nelkul konstruktor - letrehoz egy lezaro nullas C sztringet
String::String() : len(0) {
    pData = new char[len+1];
    pData[0] = '\0';
}

//Egyparameteres konstruktor letrehoz egy C sztringet, ami eltarolja a karaktert, majd lezarja a sztringet egy lezaro nullaval
String::String(char ch) {
    this->len = 1;
    this->pData = new char[len+1];
    pData[0] = ch;
    pData[1] = '\0';
}

//Letrehoz egy C sztringet egy const char* szovegbol
String::String(const char *s1) {
    this->len = strlen(s1);
    this->pData = new char[this->len+1];
    strcpy(pData, s1);
}


//A String osztaly masolo konstruktora
String::String(const String &a) {
    len = a.len;
    pData = new char[len+1];
    strcpy(pData, a.pData);
}


//A fuggveny segitsegevel megkaphatjuk a String objektum altal tartalmazott C sztring hosszat
size_t String::size() const {
    return len;
}


//A fuggveny segitsegevel visszaadhatjuk a String objektum privat adattagjat - A C sztringet
const char* String::c_str() const {
    return this->pData;
}

//Az overloaded operator= lehetove teszi az adatok dinamikus atmasolasat egyik objektumbol a masikba
String& String::operator=(const String &a) {
    if(this != &a) {
        delete[] this->pData;
        len = a.len;
        pData = new char[len + 1];
        strcpy(this->pData, a.pData);
    }
    return *this;
}

//Visszaadja a C sztring egyik karakteret
char& String::operator[](size_t a) {
    if(a<0 || a>=len) {
        throw "indexhiba";
    }
    return pData[a];
}

//Visszaadja a C sztring egyik karakteret
const char& String::operator[](size_t a) const{
    if(a<0 || a>=len) {
        throw "indexhiba";
    }
    return pData[a];
}

//Lehetove teszi, hogy ket String objektumbol letrejojjon egy harmadik a ketto osszeadasaval
String String::operator+(const String &a) const{
    String uj;
    delete[] uj.pData;
    uj.len = len + a.len;
    uj.pData = new char[uj.len + 1];
    strcpy(uj.pData, pData);
    strcat(uj.pData, a.pData);
    return uj;
}

//Lehetove teszi, hogy a String objektumhoz hozzaadodjon egy karakter - a karakterbol eloszor az egyparameteres
//konstruktor segitsegevel letrejon egy String objektum, majd meghivodik a ket String osszeado overloaded operator+
String String::operator+(char ch) const{
    return *this + String(ch);
}

//Az objektum adattagja altal foglalt dinamikus memoria az osztaly destruktoraban felszabaditasra kerul
String::~String() {
    delete[] pData;
}

//Karakterrol karakterre osszehasonlitja a ket String objektum altal tartalmazott C sztringet
// Ha a ketto megegyezik - return 0;
//Ha az elso parameterkent kapott String objektum van elorebb - return 1
//Ha a masodik parameterkent kapott String objektum van elorebb - return -1
int String::compare(const String &b) {
    int i = 0;
    while (pData[i] != '\0' && b[i] != '\0') {
        if (pData[i] < b[i]) {
            return -1;
        } else if (pData[i] > b[i]) {
            return 1;
        }
        i++;
    }
    if (pData[i] == '\0' && b[i] == '\0') {
        return 0;
    } else if (pData[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

//Az overloaded operator<< megvalositja, hogy a kimeneten megjelenjen a parameterkent kapott String objektum pData adattagja
std::ostream &operator<<(std::ostream &os, const String &a) {
    os << a.c_str();
    return os;
}


//Megvizsgalja, hogy a ket String objektum altal tartalmazott C sztringek megegyeznek-e
//return true - megegyeznek
//return false - nem egyeznek meg
bool String::operator==(String const &b) {
    if(strcmp(pData, b.c_str()) == 0) {
    return true;
    }
return false;
}