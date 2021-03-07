//
// Created by 15145 on 3/6/2021.
//

#ifndef TP1_CELLULE_H
#define TP1_CELLULE_H

#include <assert.h>
#include <iostream>

class Cellule {
public:
    Cellule();

    Cellule(int salle_x, int i_x, int y_x);

    ~Cellule();

    bool operator==(const Cellule autre) const;

    friend std::istream &operator>>(std::istream &, Cellule &);

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

bool Cellule::operator==(Cellule autre) const {
    return autre.salle == salle && autre.i == i && autre.y == y;
}

std::istream &operator>>(std::istream &is, Cellule &) {
    int salle_x, i_x, y_x;
    char a, b, c;
    is >> salle_x >> a >> i_x >> b >> y_x >> c;
    assert(a == '(' && b == ',' && c == ')');
    return is;
}


#endif //TP1_CELLULE_H
