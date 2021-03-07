#include <iostream>
#include <fstream>
#include <cassert>
#include "tableau.h"
#include "couple.h"
#include "cellule.h"

using namespace std;

int calculerNombreChemins(Tableau<Cellule> &univers, const Cellule dep, const Cellule dest) {
    int nombre = 0;
    return nombre;
}

void nombreCheminsRec(Tableau<Cellule> &univers, Cellule &dep, Cellule &dist, int &compteur) {
//todo
}


void creerTriangle(Tableau<Cellule> &univers, int numero, int dim) {
    int dist = 0;
    for (int i = 0; i < dim / 2 + 1; i++) {
        for (int y = dist; y < dim - dist; y++) {
            printf("%d (%d,%d)\n", numero, i, y);
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
        dist++;
    }
}

void creerDiamond(Tableau<Cellule> &univers, int numero, int dim) {
    int dist = dim / 2;
    for (int i = 0; i < (dim / 2) + 1; i++) {
        for (int y = dist; y < dim - dist; y++) {
            printf("%d (%d,%d)\n", numero, i, y);
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
        dist--;
    }
    dist = 1;
    for (int i = dim / 2 + 1; i < dim; i++) {
        for (int y = dist; y < dim - dist; y++) {
            printf("%d (%d,%d)\n", numero, i, y);
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
        dist++;
    }
}

void creerCaree(Tableau<Cellule> &univers, int numero, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int y = 0; y < dim; y++) {
            printf("%d (%d,%d)\n", numero, i, y);
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
    }
}

void creerUnivers(Tableau<Cellule> &univers, Tableau<Couple> &portails, istream &is) {
    while (true) {
        int compteur = 0;
        string type;
        is >> type;
        if (type == "-----")
            break; // fin de la lecture des types de salle
        int dim;
        is >> dim;
        if (type == "carre") {
            creerCaree(univers, compteur, dim);
        } else if (type == "diamant") {
            creerDiamond(univers, compteur, dim);
        } else if (type == "triangle") {
            creerTriangle(univers, compteur, dim);
        }
        compteur++;
    }
    while (!(is >> ws).eof()) {
        Cellule c1, c2;
        string fleche;
        is >> c1;
        is >> fleche;
        assert(fleche == "<-->");
        is >> c2;
        Couple temp = ::Couple(c1, c2);
        portails.ajouter(temp);
    }
}

int traiterRequetes(Tableau<Cellule> &univers, istream &is) {
    while (!(is >> ws).eof()) {
        Cellule dep, dest;
        string fleche;
        is >> dep >> fleche >> dest;
        assert(fleche == "-->");
        cout << calculerNombreChemins(univers, dep, dest) << endl;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: ./tp1 univers.txt [requetes.txt]" << endl;
        return EXIT_FAILURE;
    }
    // Lecture du fichier univers
    ifstream funivers(argv[1]);
    if (!funivers.is_open()) {
        cerr << "Erreur d'ouverture du fichier: " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    Tableau<Cellule> univers;
    Tableau<Couple> portails;
    creerUnivers(univers, portails, funivers);

    // Lecture des requêtes
    if (argc == 3) {
        ifstream frequetes(argv[2]);
        if (!frequetes.is_open()) {
            cerr << "Erreur d'ouverture du fichier: " << argv[2] << endl;
            return EXIT_FAILURE;
        }
        return traiterRequetes(univers, frequetes);
    } else
        return traiterRequetes(univers, cin);
}

