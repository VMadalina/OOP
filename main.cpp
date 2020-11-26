#include "includes/Traseu.h"
#include "includes/Marcaj.h"
#include "includes/Traseu_marcat.h"
#include "includes/Traseu_nemarcat.h"
#include <fstream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>


int main() {
    std::ifstream fin_T,  fin_M, fin_Meteo, fin_A;
    fin_T.open ("files/Traseu.txt");
    fin_M.open ("files/Marcaj.txt");
    fin_Meteo.open ("files/Meteo.txt");
    fin_A.open("files/Alegere.txt");

    srand((unsigned) time (nullptr));
    int nr_trasee = 0, nr_marcaje = 0, alegere = 0;

    if (fin_T.is_open())
        fin_T >> nr_trasee;
    else
        std::cout << "Fisierul pentru trasee nu a putut fi deschis";

    if (fin_M.is_open())
        fin_M >> nr_marcaje;
    else
        std::cout << "Fisierul pentru marcaje nu a putut fi deschis";

    Traseu traseu[nr_trasee];
    Marcaj marcaj[nr_marcaje];
    Meteo meteo[nr_trasee];
    std::vector<std::unique_ptr<Traseu_marcat>> t_marcat;
    std::vector<std::unique_ptr<Traseu_nemarcat>> t_nemarcat;

    for (int i = 0; i < nr_trasee; i++) {
        fin_T >> traseu[i];
        fin_Meteo >> meteo[i];
    }
    for (int i = 0; i < nr_marcaje; i++)
        fin_M >> marcaj[i];

    for (int i = 0; i < nr_trasee; i++) {
        if (traseu[i].get_tip_poteca() == "amenajata") {
            int random = (rand() % nr_marcaje);
            t_marcat.push_back(std::make_unique<Traseu_marcat>(marcaj[random]));
            t_marcat.back()->set_poz(i);
        }
        else {
            t_nemarcat.push_back(std::make_unique<Traseu_nemarcat>(traseu[i]));
            t_nemarcat.back()->set_poz(i);
        }
    }

    ///punem in fisier 1 pentru traseele marcate si 2 daca vrem sa alegem un traseu nemarcat
    fin_A >> alegere;
    if (alegere == 1) {
        int random = (rand() % t_marcat.size());
        std::cout << *t_marcat[random];
        int random_vreme = (rand() % nr_trasee);
        std::cout << meteo[random_vreme];
        std::cout << t_marcat[random]->timp_traseu_marcat(traseu[t_marcat[random]->get_poz()]) + meteo[random_vreme].influenta_vreme() << " ore.\n";
    }
    else {
        int random = (rand() % t_nemarcat.size());
        std::cout << random << "\n";
        int random_vreme = (rand() % nr_trasee);
        std::cout << *t_nemarcat[random];
        std::cout << meteo[random_vreme];
        std::cout << t_nemarcat[random]->timp_traseu_nemarcat(traseu[t_nemarcat[random]->get_poz()]) + meteo[random_vreme].influenta_vreme() << " ore.\n";
        t_nemarcat[random]->obiectiv_nou(meteo[random_vreme]);
    }

    t_marcat.clear();
    t_nemarcat.clear();
    fin_T.close();
    fin_M.close();
    fin_Meteo.close();
    fin_A.close();

    return 0;
}
