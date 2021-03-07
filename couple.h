//
// Created by 15145 on 3/6/2021.
//

#ifndef TP1_COUPLE_H
#define TP1_COUPLE_H

#include "tableau.h"
#include "cellule.h"

class Couple {
public:
    Couple();

    Couple(Cellule &a, Cellule &b);

    ~Couple();

    Cellule contient(const Cellule cellule) const;

private:
    Cellule A;
    Cellule B;
};

Couple::Couple(Cellule &a, Cellule &b) {
    A = a;
    B = b;
}

Couple::Couple(){
}

Couple::~Couple(){
}

#endif //TP1_COUPLE_H
