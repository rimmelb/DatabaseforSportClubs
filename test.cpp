
#ifndef CPORTA //n betűt szedd k jporta beadásnál

#include <iostream>
#include <sstream>
#include <clocale>
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
# include <windows.h>
#endif
 // a standard header-ek után kell lennie
#include "gtest_lite.h"
#include "String.h"
#include "Egyesulet.h"
#include "Szemelyzet.h"

#define ELKESZULT 34

using std::cout;
using std::cin;
using std::endl;

int main() {
    GTINIT(std::cin);       // Csak C(J)PORTA működéséhez kell

#if ELKESZULT >= 0
    TEST(Elkeszult0, construct) {
            std::cout << "Udvozoljuk a Soproni Sportegyesulet honlapjan!\nMiben segithetunk?" << std::endl;
            size_t valasztas;
            size_t valaszt_belul;
            Egyesulet egyesulet("input.txt");
            do {
                valasztas = valasztasellenorzo();

                switch(valasztas) {
                    case 1: {
                        do {
                            valaszt_belul = valasztasellenorzo_case1();
                            switch (valaszt_belul) {
                                case 1:
                                    egyesulet.details_of_egyesulet();
                                    break;

                                case 2: {
                                    size_t kiadasvaltoztat = kiadasellenorzo();
                                    egyesulet.kiadasSet(kiadasvaltoztat);
                                }
                                    break;

                                case 3: {
                                    size_t bevetelvaltoztat = bevetelellenorzo();
                                    egyesulet.bevetelSet(bevetelvaltoztat);
                                }
                                    break;
                            }


                        } while (valaszt_belul != 0);
                    }
                        break;

                    case 2: {
                        do {
                            valaszt_belul = valasztasellenorzo_case2();
                            switch (valaszt_belul) {
                                case 1:
                                    egyesulet.print_out_vezetok();
                                    break;
                                case 2: {
                                    size_t torles = delete_vezeto_check(egyesulet);
                                    egyesulet.remove_Vezetok(torles);
                                }
                                    break;
                                case 3:
                                    kilistaz_vezetok(egyesulet);
                                    break;
                            }
                        } while (valaszt_belul != 0);
                    }
                        break;


                    case 3:
                        do {
                            valaszt_belul = valasztasellenorzo_case3();

                            switch(valaszt_belul) {
                                case 1 : csapatkilistaz_ellenorzo(egyesulet);
                                    break;
                                case 2 : adott_csapatbol_torles(egyesulet);
                                    break;
                                case 3: adott_csapathoz_hozzaadas(egyesulet);
                                    break;
                                case 4: adott_jatekossal_szerzodeshosszabbitas(egyesulet);
                                    break;
                                case 5: adott_jatekos_fizetesvaltoztatas(egyesulet);
                                    break;
                                case 6: adott_csapatbol_listazas(egyesulet);
                                    break;
                                case 7: adott_csapatban_kereses(egyesulet);
                                    break;
                                case 8: csapat_torles(egyesulet);
                                    break;
                                case 9:
                                    csapat_hozzaadas(egyesulet);
                                    break;
                            }
                        }while (valaszt_belul != 0);
                        break;

                    case 4:
                    {
                        std::cout << "Koszonjuk, hogy meglatogatta az oldalunkat! Szep napot kivanunk!";
                        egyesulet.print_to_file("input.txt");
                    }
                        //ha 0 bemenet erkezik akkor mindig vissza tud az adott fuggvenybol lepni a kezdeti do while switchbe
                }
            }while(valasztas != 4);
        } ENDM
#endif

/**
 *  1. A paraméter nélkül hívható konstruktora üres sztringet hozzon étre!
 */
#if ELKESZULT >= 1
    TEST(Elkeszult1, construct) {
            String ures;
            if (ures.size() != 0)
                FAIL() << "Baj van a string hosszaval" << endl;
#ifndef CPORTA
            else
                SUCCEED() << "Mukodik!" << endl;
#endif // CPORTA
        }
            ENDM
#endif

/**
 *  2. Van olyan tagfüggvénye ( c_str() ), ami C-sztringgel, azaz nullával lezárt
 *     karaktersorozatra mutató pointerel (const char *) tér vissza.
 */
#if ELKESZULT >= 2
    TEST(Elkeszult2, emptyStr) {
            String ures;
            EXPECT_EQ((size_t) 0, ures.size()) << "Baj van a string hosszaval" << endl;

            EXPECT_STREQ("", ures.c_str()) << "NULL pointer jott letre" << endl;
        }
            ENDM
#endif

/**
 * 3. Van olyan konstruktora, ami karakterből hoz létre sztringet.
 */
#if ELKESZULT >= 3
    TEST(Elkeszult3, fromChr) {
            char ch = 'a';
            String a(ch);
            EXPECT_EQ((size_t) 1, a.size()) << "Baj van a string hosszaval" << endl;
            EXPECT_STREQ("a", a.c_str()) << "Karakterbol sztring letrehozasa nem sikerult!" << endl;

            String b('a');    // konstansból is megy?
            EXPECT_STREQ("a", b.c_str()) << "Karakterbol sztring letrehozasa nem sikerult!" << endl;
        }
            ENDM
#endif

/**
 *  4. Van olyan konstruktora, ami C-sztringből (const char*) hoz létre sztringet.
 *  A const char* konstruktor lemásolja a sztringet, nem csak a pointert!
 */
#if ELKESZULT >= 4
    TEST(Elkeszult4, FromCstr) {
            const char *hello = "Hello sztring";
            String a(hello);
            EXPECT_EQ(strlen(hello), a.size()) << "Baj van a string hosszaval" << endl;
            EXPECT_STREQ(hello, a.c_str()) << "C-sztringbol string letrehozasa nem sikerult!" << endl;

            /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
            char cpp[] = {'C', '+', '+', '\0'};
            String b(cpp);
            cpp[0] = 'X';
            EXPECT_STRNE(cpp, b.c_str()) << "FromCstr: le kellett volna masolni a karaktertombot!" << endl;
        }
            ENDM
#endif

/**
 *  5. Az osztályból létrehozott objektum legyen átadható értékparaméterként!
 */
#if ELKESZULT >= 5
    TEST(Elkeszult5, ctor) {
            const char *hello = "Hello sztring";
            String a(hello);
            String b = a;
            EXPECT_EQ(strlen(hello), b.size()) << "Baj van a string hosszaval!" << endl;
            EXPECT_STREQ(hello, b.c_str()) << "Baj van a masolo konstruktorral!" << endl;

            /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
            if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
                FAIL() << "!** ctor: nem elegendo a pointereket lemasolni!" << endl;

            EXPECT_STREQ(hello, a.c_str()) << "Masolo kontsr. elromlott a forras!" << endl;
            EXPECT_EQ(strlen(hello), a.size()) << "Masolo konstr. alatt elromlott a forras hossza!" << endl;

            const String c = a;
            String d = c;     // konstansból is megy?
            EXPECT_STREQ(hello, d.c_str()) << "Baj van a masolo konstruktorral" << endl;
        }
            ENDM

    TEST(Elkeszult5, ctor_nullptr)
        {
            String d0;
            String ures = d0;     // üres sztringet is le tudja másolni?
            EXPECT_EQ((size_t) 0, ures.size()) << "Baj van a string hosszaval" << endl;
            /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
            EXPECT_STREQ("", ures.c_str()) << "Nem ures sztring jott letre" << endl;
        }
            ENDM
#endif

/**
 *  6. Támogassa a többszörös értékadást (b = a = a)!
 */
#if ELKESZULT >= 6
    TEST(Elkeszult6, opAssign) {
            const char *hello = "Hello sztring";
            String a(hello);
            String b("Duma1"), c("Duma2");
            EXPECT_STRNE(a.c_str(), b.c_str());
            a = a;
            EXPECT_EQ(strlen(hello), a.size()) << "Baj van az ertekadassal: a = a hossz" << endl;
            EXPECT_STREQ(hello, a.c_str()) << "Baj van az ertekadassal: a = a" << endl;
            c = b = a;

            /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
            if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
                FAIL() << "!** op=: nem elegendo a pointereket lemasolni!" << endl;

            EXPECT_EQ(strlen(hello), a.size()) << "Ertekedasnal elromlott a forras hossza!" << endl;
            EXPECT_STREQ(hello, a.c_str()) << "Ertekadasnal elromlott a forras!" << endl;
            EXPECT_EQ(strlen(hello), b.size()) << "Ertekedas: nem jo a hossz!" << endl;
            EXPECT_STREQ(hello, b.c_str()) << "Ertekadas nem sikerult!" << endl;
            EXPECT_EQ(strlen(hello), c.size()) << "Ertekedas: nem jo a hossz!" << endl;
            EXPECT_STREQ(hello, c.c_str()) << "Ertekadas nem sikerult!" << endl;

            const String d("Konst.");
            c = d;        // konstansból is megy?
            EXPECT_EQ(c.size(), c.size()) << "Ertekedas konstansbol: nem jo a hossz!" << endl;
            EXPECT_STREQ(d.c_str(), c.c_str()) << "Ertekadas konstansbol nem sikerult!" << endl;
        }
            ENDM

    TEST(Elkeszult6, opAssign_nullptr) {
            String d0;
            String c = d0;     // üres sztringet is le tudja másolni?
            EXPECT_EQ((size_t) 0, c.size()) << "Baj van a string hosszaval" << endl;
            /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
            EXPECT_STREQ("", c.c_str()) << "Nem ures sztring jott letre" << endl;

        }
            ENDM
#endif

/**
 *  7. Legyenek olyan operátorai (operator+), amivel a sztring végéhez sztringet
 *     és karaktert lehet fűzni!
 */
#if ELKESZULT >= 7
    TEST(Elkeszult7, strPlusStr) {
            String a("Hello ");
            String b("sztring");
            String c;
            c = a + b;
            EXPECT_STREQ("Hello sztring", c.c_str()) << "Nem sikerult a + String muvelet!" << endl;
            EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << endl;
            EXPECT_STREQ("sztring", b.c_str()) << "A + muvelet elrontja a jobb oldalt?" << endl;
            const String a1 = a, b1 = b;

            String c1;
            c1 = a1 + b1;          // konstansból is megy?
            EXPECT_STREQ("Hello sztring", c1.c_str()) << "Nem sikerult a + String muvelet!" << endl;
        }
            ENDM

    TEST(Elkeszult7, strPlusChr) {
            String a("Hello ");
            String b;
            b = a + 'B';
            EXPECT_STREQ("Hello B", b.c_str()) << "Nem sikerult a + char muvelet!" << endl;
            EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << endl;

            const String a1 = a;
            String b1;
            b1 = a1 + 'B';          // konstansból is megy?
            EXPECT_STREQ("Hello B", b1.c_str()) << "Nem sikerult a + char muvelet!" << endl;
            EXPECT_STREQ("Hello ", a1.c_str()) << "A + muvelet elrontja a bal oldalt?" << endl;

        }
            ENDM
#endif

/*************************Sztring osztaly teszt********************************/

/**
 * 8. meghivja a fajlbol beolvaso konstruktort az egyesulet objektumra, majd bezarja a fajlt;
 */
#if ELKESZULT >= 8
    TEST(Elkeszult8, fajlmegnyitas) {
            Egyesulet egyesulet("test.txt");
            if (egyesulet.getVezetokmeret() == 7) {
                std::cout << "A beolvasas helyes!\n";
            } else {
                std::cout << "Nem sikeres a fajlbeolvasas!\n";
            }
        } ENDM
#endif

#if ELKESZULT >= 9
    TEST(Elkeszult9, egyesulet_adat_megjelenit) {
        Egyesulet a("test.txt");
        a.details_of_egyesulet();
    } ENDM
#endif


#if ELKESZULT >=10
    TEST(ELKESZULT10, egyesulet_kiadas_megvaltoztat) {
    Egyesulet egyesulet("test.txt");
    if(egyesulet.getcsapatszam() == 3) {
        std::cout << "Sikeres, jelenleg 3 csapat van!\n";
    }
    else {
        std::cout << "Jelenleg 3 csapat van\n";
    }
    } ENDM
#endif

#if ELKESZULT >= 11
    TEST(ELKESZULT11, egyesulet_bevetel_megvaltoztat) {
    Egyesulet egyesulet("test.txt");

    size_t elso = egyesulet.getBevetel();
    egyesulet.bevetelSet(1000000);
    if(egyesulet.getBevetel() == elso + 1000000) {
        std::cout << "Mukodik a bevetelvaltoztatas!\n";
    }
    else {
        std::cout << "Nem mukodik a bevetelvaltoztatas!\n";
    }
    } ENDM
#endif

#if ELKESZULT >= 12
    TEST(ELKESZULT12, egyesulet_kiadas_megvaltoztat) {
    Egyesulet egyesulet("test.txt");
            size_t elso = egyesulet.getKiadas();
            egyesulet.kiadasSet(1000000);

            if(egyesulet.getKiadas() == elso + 1000000) {
                std::cout << "Mukodik a kiadasvaltoztatas!\n";
            }
            else {
                std::cout << "Nem mukodik a kiadvaltoztatas!\n";
            }
    } ENDM
#endif

#if ELKESZULT >= 13
    TEST(ELKESZULT13, egyesulet_kiir_vezetok) {
    Egyesulet egyesulet("test.txt");
    egyesulet.print_out_vezetok();
    } ENDM
#endif


#if ELKESZULT >= 14
    TEST(ELKESZULT14, egyesulet_remove_Vezetok) {
            String s("5\nKovacs\nJanos\n1000000\n2\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            size_t torles = delete_vezeto_check(egyesulet, ss);
            egyesulet.remove_Vezetok(torles, ss);
            egyesulet.print_out_vezetok();

        } ENDM
#endif


#if ELKESZULT >= 15
    TEST(ELKESZULT15, Jatekos_konstruktor_teszt) {
        String nev("Nagy Viktor");
        size_t fz = 100000;
        size_t szulev = 1996;
        size_t mezsz = 10;
        size_t csapatsz = 2;
        size_t szhatra = 4;
        Jatekosok uj(nev, fz, mezsz, szulev, szhatra, csapatsz);
            if(uj.getNev() == nev && uj.getFiz() == fz && uj.getSzulev() == szulev) {
                std::cout << "Mukodik a Jatekosok konstruktor\n";
            }
            else {
                std::cout << "Nem mukodik a Jatekosok konstruktor\n";
            }
        } ENDM
#endif



#if ELKESZULT >= 16
    TEST(ELKESZULT16, Szemelyzet_konstruktor_teszt) {
            String nev("Nagy Imre");
            size_t fz = 100000;
            size_t csapatsz = 2;
            String foglalkoz("szakvezeto");
            String vegzettseg("egyetem");
            Szemelyzet uj(nev, fz, csapatsz, foglalkoz, vegzettseg);
            if(uj.getNev() == nev && uj.getFiz() == fz && uj.getfoglal() == foglalkoz && uj.getvegzett() == vegzettseg) {
                std::cout << "Mukodik a Szemelyzet konstruktor\n";
            }
            else {
                std::cout << "Nem mukodik a Szemelyzet konstruktor\n";
            }
        } ENDM
#endif

#if ELKESZULT >= 17
    TEST(ELKESZULT17, Vezetok_konstruktor teszt) {
            String nev("Nagy Imre");
            size_t fz = 100000;
            String foglal("szakvezeto");
            String vegzettseg("egyetem");
            Vezetok uj(nev, fz, foglal, vegzettseg);
            if(uj.getNev() == nev && uj.getFiz() == fz && uj.getFoglalkozas() == foglal && uj.getVegzettseg() == vegzettseg) {
                std::cout << "Mukodik a Vezetok konstruktor\n";
            }
            else {
                std::cout << "Nem mukodik a Vezetok konstruktor\n";
            }
        } ENDM
#endif

#if ELKESZULT >= 18
    TEST(ELKESZULT18, egyesulet_rendez_Vezetok_ABC) {
            String s("1\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            kilistaz_vezetok(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 19
    TEST(ELKESZULT19, egyesulet_rendez_Vezetok_fizetes) {
            String s("2\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            kilistaz_vezetok(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 20
    TEST(ELKESZULT20, egyesulet_csapatkilistaz_ellenorzo) {
            String s("1\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            csapatkilistaz_ellenorzo(egyesulet, ss);
        } ENDM
#endif


#if ELKESZULT >= 21
    TEST(ELKESZULT21, egyesulet_adott_csapatbol_torles_Szemelyzet) {
            String s("1\n1\n2\nNemeth\nGabor\n500000\n2\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatbol_torles(egyesulet, ss);
            egyesulet.print_selected_csapat(0);
        } ENDM
#endif


#if ELKESZULT >= 22
    TEST(ELKESZULT22, egyesulet_adott_csapatbol_torles_Jatekos) {
            String s("1\n2\n2\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatbol_torles(egyesulet, ss);
            egyesulet.print_selected_csapat(0);
        } ENDM
#endif

#if ELKESZULT >= 23
    TEST(ELKESZULT23, egyesulet_csapathoz_hozzaadas) {
            String s("1\nNemeth\nGabor\n200000\n20\n5\n1986\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapathoz_hozzaadas(egyesulet, ss);
            egyesulet.print_selected_csapat(0);
        } ENDM
#endif

#if ELKESZULT >= 24
    TEST(ELKESZULT24, egyesulet_adott_jatekos_szerzodeshosszabbitas) {
            String s("1\n2\n5\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_jatekossal_szerzodeshosszabbitas(egyesulet, ss);
            egyesulet.print_selected_csapat(0);
        } ENDM
#endif

#if ELKESZULT >= 25
    TEST(ELKESZULT25, egyesulet_adott_jatekos_fizetesvaltoztatas) {
            String s("1\n3\n200000\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_jatekos_fizetesvaltoztatas(egyesulet, ss);
            egyesulet.print_selected_csapat(0);
        } ENDM
#endif


#if ELKESZULT >= 26
    TEST(ELKESZULT26, egyesulet_adott_csapatbol_listazas_szuletesi_ev) {
            String s("1\n1\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatbol_listazas(egyesulet, ss);
        } ENDM
#endif


#if ELKESZULT >= 27
    TEST(ELKESZULT27, egyesulet_adott_csapatbol_listazas_hatralevo_szerzodes) {
            String s("1\n2\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatbol_listazas(egyesulet, ss);
        } ENDM
#endif


#if ELKESZULT >= 28
    TEST(ELKESZULT28, egyesulet_adott_csapatbol_listazas_fizetes) {
            String s("1\n3\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatbol_listazas(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 29
    TEST(ELKESZULT29, egyesulet_adott_csapatbol_listazas_mezszam) {
            String s("1\n4\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatbol_listazas(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 30
    TEST(ELKESZULT30, egyesulet_adott_csapatban_kereses_ev_szerint) {
            String s("1\n1\n1990\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatban_kereses(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 31
    TEST(ELKESZULT31, egyesulet_adott_csapatban_kereses_hatralevo_szerzodes_szerint) {
            String s("1\n2\n3\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatban_kereses(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 32
    TEST(ELKESZULT32, egyesulet_adott_csapatban_kereses_hatralevo_fizetes_szerint) {
            String s("1\n3\n800000\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            adott_csapatban_kereses(egyesulet, ss);
        } ENDM
#endif

#if ELKESZULT >= 33
    TEST(ELKESZULT33, egyesulet_adott_csapat_torles) {
            String s("1\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            csapat_torles(egyesulet, ss);
            for(size_t x = 0; x < egyesulet.getcsapatszam(); x++) {
                egyesulet.print_selected_csapat(x);
            }
        } ENDM
#endif


#if ELKESZULT >= 34
    TEST(ELKESZULT34, egyesulet_adott_csapat_hozzaadas) {
            String s("roplabda\nNagy\nArpad\n100000\n1\nHorvath\nJanos\n100000\n2\nNagy\nGabor\n200000\n2\n"
                     "Toth\nVilmos\n100000\n2\nJuhasz\nGeza\n1000000\n1\nNagy\nEzekiel\n100000\n1\n"
                     "Fodor\nArpad\n100000\n1976\n5\nNemeth\nGeza\n100000\n1978\n2\nRoth\nGyula\n100000\n1980\n4\n"
                     "Nemeth\nLaszlo\n100000\n1978\n2\nKovacs\nGyula\n100000\n1980\n4\n");
            std::stringstream ss;
            ss << s.c_str();
            Egyesulet egyesulet("test.txt");
            csapat_hozzaadas(egyesulet, ss);
            egyesulet.print_selected_csapat(3);
        } ENDM
#endif

return 0;
}

#endif