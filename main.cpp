#include <iostream>
#include <fstream>
#include <cassert>
#include "tableau.h"
#include "couple.h"
#include "cellule.h"

using namespace std;

Cellule lireCellule(istream &is){
    int salle_x, i_x, y_x;
    char a, b, c;
    is >> salle_x >> a >> i_x >> b >> y_x >> c;
    assert(a == '(' && b == ',' && c == ')');
    Cellule temp = ::Cellule(salle_x, i_x, y_x);
    return temp;
}

void nombreCheminsRec(Tableau<Cellule> &univers,Tableau<Couple> &portails, Cellule &dep, Cellule &dest, int &compteur) {
    if ( dep == dest ) {
    compteur++;
} else {
    Tableau<Cellule> voisins = dep.retournerVoisins(univers,portails);
    for (int i = 0; i < voisins.taille(); i++){
        nombreCheminsRec(univers, portails, voisins[i],dest, compteur);
        voisins[i].rendreDispo();
}
}
}


int calculerNombreChemins(Tableau<Cellule> &univers,  Tableau<Couple> &portails, Cellule &dep,  Cellule &dest, int &compteur) { 
     if ( univers.chercher(dep) >= 0 && univers.chercher(dest) >= 0){
         compteur = 0;
         dep.rendreNonDispo();
         nombreCheminsRec(univers, portails, dep, dest, compteur);
         return compteur;
}
     return -1;
}



void creerTriangle(Tableau<Cellule> &univers, int numero, int dim) {
printf("creation triangle %d avec succes\n", numero);    
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
printf("creation diamond %d avec succes\n", numero); 
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
    printf("Carre %d cree avec succes\n", numero);
	for (int i = 0; i < dim; i++) {
        for (int y = 0; y < dim; y++) {
            printf("%d (%d,%d)\n", numero, i, y);
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
    }
}

void creerUnivers(Tableau<Cellule> &univers, Tableau<Couple> &portails, istream &is) {
int compteur = 0;
    while (true) {
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
        c1 = lireCellule(is);
        is >> fleche;
        assert(fleche == "<-->");
        c2 = lireCellule(is);
        Couple temp = ::Couple(c1, c2);
        portails.ajouter(temp);
    }
}

int traiterRequetes(Tableau<Cellule> &univers, Tableau<Couple> &portails, istream &is) {
    while (!(is >> ws).eof()) {
        Cellule dep, dest;
        string fleche;
        dep = lireCellule(is);
        is >> fleche;
        dest = lireCellule(is);
        int compteur = 0;
        cout << calculerNombreChemins(univers,portails, dep, dest, compteur) << endl;
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
    printf("FIN %d cellules\n", univers.taille() );
    printf("Nombre des portails = %d\n", portails.taille());

    // Lecture des requêtes
    if (argc == 3) {
        ifstream frequetes(argv[2]);
        if (!frequetes.is_open()) {
            cerr << "Erreur d'ouverture du fichier: " << argv[2] << endl;
            return EXIT_FAILURE;
        }
        return traiterRequetes(univers, portails, frequetes);
    } else
        return traiterRequetes(univers, portails, cin);
}

