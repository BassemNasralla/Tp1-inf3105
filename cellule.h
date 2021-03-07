//
// Created by 15145 on 3/6/2021.
//

#ifndef TP1_CELLULE_H
#define TP1_CELLULE_H

#include <assert.h>
#include <iostream>
#include "tableau.h"

class Cellule {
public:
    Cellule();

    Cellule(int salle_x, int i_x, int y_x);

    ~Cellule();
     
    void rendreDispo();
    
    void rendreNonDispo();
    
    bool estVisite();

    int afficher();

    bool operator==(const Cellule autre) const;


template<class T>
friend class Tableau;


private:
    int salle;
    int i;
    int y;
    bool visite;
};

Cellule::Cellule(int salle_x, int i_x, int y_x) {
    salle = salle_x;
    i = i_x;
    y = y_x;
    visite = false;
}

Cellule::Cellule(){
}

Cellule::~Cellule(){
}

bool Cellule::operator==(Cellule autre) const {
    return autre.salle == salle && autre.i == i && autre.y == y;
}

bool Cellule::estVisite() {
return visite;
}

void Cellule::rendreDispo() {
visite = false;
}

void Cellule::rendreNonDispo() {
visite = true;
}


int Cellule::afficher(){
printf("\n\n %d (%d,%d) \n", salle, i, y);
return i;
}
#endif //TP1_CELLULE_H
