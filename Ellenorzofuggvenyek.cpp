#include "Ellenorzofuggvenyek.h"
#include "memtrace.h"

//Ellenorzi, hogy a parameterkent kapott String objektum c-sztring adattagja csak betut tartalmaz-e
bool is_valid(String const &a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (std::isalpha(a[i]) == 0) {
            return false;
        }
    }
    return true;
}

//Ellenorzi, hogy van-e az adott szovegben szamtol kulonbozo karakter
bool is_there_a_character(String const &a) {
    for(size_t i = 0; i < a.size(); i++) {
        if(!(isdigit(a[i]))) {
            return true;
        }
    }
    return false;
}

//Atalakit egy c-stringet egy szamma
size_t convertToNumber(const char* s) {
    size_t result = 0;
    size_t sign = 1;
    size_t i = 0;

    //Vegigmegy a string osszes tagjan
    while (s[i] != '\0') {
        //A string osszes tagjat atalakitja szamma
        size_t digit = s[i] - '0';

        //Megnezi, hogy biztosan szam-e
        if (digit >= 0 && digit <= 9) {
            //Megszorozza a korabbi eredmenyt 10-el, majd hozzaadja az uj szamot
            result = result * 10 + digit;
        } else {
            std::cout << "Nem jo a bemenet!\n";
            //Ha rossz a bemenet, akkor return -1;
            return -1;
        }

        i++;
    }

    //Visszaadja a szamot
    return result * sign;
}

size_t ellenorzofuggveny(char *const &a, size_t hatar1, size_t hatar2, std::istream& is) {
    size_t szam;
    //Legfeljebb 50 karaktert tud beolvasni
    char s[50];
    do {
        //Kiirja a szoveget
        std::cout << a;
        std::cout << "Kerem " << hatar1 << " es " << hatar2 << " kozotti szamot adjon meg!\n";
        is >> s;
        String uj(s);
        //Ha igazzal ter vissza, akkor ujra beolvassa
        while(is_there_a_character(uj)) {
            std::cout << "Helytelen bemenet! Probalja ujra!\n";
            is >> s;
            String ujra(s);
            uj = ujra;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        //Meghivja a convertToNumber fuggvenyt
        szam = convertToNumber(s);
        //Ha nem teljesul, akkor az egesz indul elolrol
        if(szam < hatar1 || szam > hatar2) {
            std::cout << "Helytelen tartomany! Probalja ujra!\n";
        }
    }while(szam < hatar1 || szam > hatar2);
    //Visszater a szammal
    return szam;
}

//Az itt levo negy segedfuggveny a bubblesort_jatekosok fuggvenyben jatszanak szerepet
//A compare_szulev visszaadja,hogy az elso parameterkent kapott Jatekosok objektumnak nagyobb-e a szulev adattagja, mint a masodik parameterkent kapott Jatekosok objektumnak
bool compare_szulev(Jatekosok *elso, Jatekosok *masodik) {
    return elso->getSzulev() > masodik->getSzulev();
}
//A compare_szerzodes_hatra visszaadja,hogy az elso parameterkent kapott Jatekosok objektumnak nagyobb-e a szerzodes_hatra adattagja, mint a masodik parameterkent kapott Jatekosok objektumnak
bool compare_szerzodes_hatra(Jatekosok *elso, Jatekosok *masodik) {
    return elso->getSzerzodes() > masodik->getSzerzodes();
}

//A compare_fizetes visszaadja,hogy az elso parameterkent kapott Jatekosok objektumnak nagyobb-e a fizetes adattagja, mint a masodik parameterkent kapott Jatekosok objektumnak
bool compare_fizetes(Jatekosok *elso, Jatekosok *masodik) {
    return elso->getFiz() > masodik->getFiz();
}

//A compare_szulev visszaadja,hogy az elso parameterkent kapott Jatekosok objektumnak nagyobb-e a mezszam adattagja, mint a masodik parameterkent kapott Jatekosok objektumnak
bool compare_mezszam(Jatekosok *elso, Jatekosok *masodik) {
    return elso->getMsz() > masodik->getMsz();
}

//A kovetkezo fuggvenyek a menuvezerelt programban fontos szerepet jatszanak - meghivjak az elobbi ellenorzo fuggvenyt, melynek atadjak a megfelelo szoveget,
//melyet az megjeleniti a szabvanyos bemeneten, majd a kapott, mar a parametereknek megfelelo szamot visszaadjak
size_t valasztasellenorzo() {
    char f[100] = "1 - Egyesulet adatai\n2 - Vezetoseg\n3 - Csapatok\n4 - Kilepes\n";
    size_t sz = ellenorzofuggveny(f, 1, 4);
    return sz;

}

size_t valasztasellenorzo_case1() {
    char f[200] = "1 - Egyesulet adatainak megtekintese\n2 - kiadas valtoztatasa\n3 - bevetel valtoztatasa\n0 - Visszalepes\n";
    size_t szam = ellenorzofuggveny(f, 0, 3);
    return szam;
}

size_t kiadasellenorzo() {
    char f[100] = "Kerem, adja meg, hogy mennyivel valtozott meg a kiadas!\n";
    size_t szam = ellenorzofuggveny(f, 0, 1000000000);
    return szam;
}

size_t bevetelellenorzo() {
    char f[100] = "Kerem, adja meg, hogy mennyivel valtozott meg a bevetel!\n";
    size_t szam = ellenorzofuggveny(f, 0, 10000000000);
    return szam;
}

size_t valasztasellenorzo_case2() {
    char f[200] = "1 - Vezetoseg osszetetele\n2 - Vezeto torlese, uj vezeto felvetele\n3 - Listazas szempont szerint\n0 - Visszalepes\n";
    size_t szam = ellenorzofuggveny(f, 0, 3);
    return szam;
}

size_t valasztasellenorzo_case3() {
    char f[300] = "\n1 - Adott csapat megtekintese\n2 - Csapat kivalasztasa szemelyzet/jatekos torlesre\n3 - Uj jatekos hozzaadasa adott csapathoz\n4 - Szerzodeshosszabbitas"
                  "\n5 - fizetesvaltoztatas\n6 - Listazas\n7 - Kereses\n8 - Csapat torlese\n9 - Uj csapat hozzaadasa\n0 - Visszalepes\n";
    size_t szam = ellenorzofuggveny(f, 0, 9);
    return szam;
}

size_t fizetesellenorzo(std::istream& is) {
    char f[50] = "Kerem, adja meg, hogy mennyi a fizetese!\n";
    size_t szam = ellenorzofuggveny(f, 0, 100000000, is);
    return szam;

}

size_t szerzodes_ellenorzo(std::istream& is) {
    char f[50] = "Hatralevo szerzodeshossz: \n";
    size_t szam = ellenorzofuggveny(f, 0, 10, is);
    return szam;
}

size_t szuletesiev_ellenorzo(std::istream& is) {
    char f[50] = "Szuletesi ev: \n";
    size_t szam = ellenorzofuggveny(f, 1970, 2010, is);
    return szam;
}

//Visszaadja a felhasznalo altal valasztott vegzettseget
String vegzettsegellenorzo(std::istream& is) {
    char f[100] = "Kerem, adja meg, hogy az alabbiak kozul mi a vegzettsege!\n1 - egyetem\n2 - foiskola\n3 - gimnazium\n";
    size_t szam = ellenorzofuggveny(f, 1, 3, is);

    switch(szam) {
        case 1 :
            return {"egyetem"};
        case 2:
            return {"foiskola"};
        case 3:
            return {"gimnazium"};
        default:
            return {"gimnazium"};
    }
}

//Ellenorzi, hogy a felhasznalo helyes bemenetet adott-e meg az elobbi fuggveny felhasznalasaval
String get_valid_name(const char *szoveg, std::istream& is) {
    bool valid = false;
    char nev[51];
    while (!valid) {
        std::cout << szoveg; //legfeljebb 50 karakter hosszu lehet
        is >> nev;
        String str(nev);
        if(!is_valid(str)) {
            std::cout << "Helytelen bemenet! Probalja ujra!\n";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            valid = true;
            return str;
        }
    }
    return String();
}

//Az elozo fuggveny felhasznalasaval elkesziti a felhasznalo altal beirt adatokbol a megfelelo objektumnak a nev adattagjat
String nevellenorzo(std::istream& is) {
    String vezeteknev = get_valid_name("Kerem a vezeteknevet (legfeljebb 50 karakter, csak az angol abc betui):\n", is);
    String keresztnev = get_valid_name("Kerem a keresztnevet(legfeljebb 50 karakter, csak az angol abc betui):\n", is);

    String enter = String(" ");
    String nev = vezeteknev + enter + keresztnev;

    return nev;
}
