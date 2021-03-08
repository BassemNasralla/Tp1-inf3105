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

    Tableau<int> retournerVoisins(Tableau<Cellule> &univers, Tableau<Cellule> &portails);


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

Tableau<int> Cellule::retournerVoisins(Tableau<Cellule> &univers, Tableau<Cellule> &portails){

Tableau<int> voisins;
Cellule tmp1, tmp2, tmp3, tmp4;

tmp1 = Cellule(salle, i-1, y);
tmp2 = Cellule(salle, i+1, y);
tmp3 = Cellule(salle, i, y-1);
tmp4 = Cellule(salle,i, y+1);

int indice1 = univers.chercher(tmp1);
int indice2 = univers.chercher(tmp2);
int indice3 = univers.chercher(tmp3);
int indice4 = univers.chercher(tmp4);
int indice5;

for ( int x = 0; x < portails.taille(); x = x+2){
if(*this == portails[x] ) {
indice5 = univers.chercher(portails[x+1]);
}
if (*this == portails[x+1] ) {
indice5 = univers.chercher(portails[x]);
}
}

if (indice1 >= 0){
voisins.ajouter(indice1);
}
if (indice2 >= 0){
voisins.ajouter(indice2);
}
if (indice3 >= 0){
voisins.ajouter(indice3);
}
if (indice4 >= 0){
voisins.ajouter(indice4);
}
if (indice5 >= 0){
voisins.ajouter(indice5);
}


return voisins;
}
#endif //TP1_CELLULE_H
