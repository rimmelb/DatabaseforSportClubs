
#ifndef CPORTA

#include <iostream>
#include <fstream>
#include "Egyesulet.h"
#include "memtrace.h"

int main() {
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
               return 0;
           }
           //ha 0 bemenet erkezik akkor mindig vissza tud az adott fuggvenybol lepni a kezdeti do while switchbe
       }
    }while(valasztas != 4);
}
#endif