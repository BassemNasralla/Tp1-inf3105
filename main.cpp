#include <iostream>
#include <fstream>
#include <cassert>
#include "tableau.h"
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

void nombreCheminsRec(Tableau<Cellule> &univers,Tableau<Cellule> &portails, Cellule &dep, Cellule &dest, int &compteur) {
    if ( dep == dest ) {
    compteur++;
} else {
    Tableau<int> voisins = dep.retournerVoisins(univers, portails);
    for (int i = 0; i < voisins.taille(); i++){
      if (!univers[voisins[i]].estVisite() ){
         univers[voisins[i]].rendreNonDispo();
         nombreCheminsRec( univers, portails, univers[voisins[i]], dest, compteur);
         univers[voisins[i]].rendreDispo();
}
}
}
}


int calculerNombreChemins(Tableau<Cellule> &univers,  Tableau<Cellule> &portails, Cellule &dep,  Cellule &dest, int &compteur) { 
     if ( univers.chercher(dep) >= 0 && univers.chercher(dest) >= 0){
if(dep == dest ){
return 0;
}
         compteur = 0;
         dep.rendreNonDispo();
         nombreCheminsRec(univers, portails, dep, dest, compteur);
         return compteur;
}
     return -1;
}



void creerTriangle(Tableau<Cellule> &univers, int numero, int dim) {
int dist = 0;
    for (int i = 0; i < dim / 2 + 1; i++) {
        for (int y = dist; y < dim - dist; y++) {
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
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
        dist--;
    }
    dist = 1;
    for (int i = dim / 2 + 1; i < dim; i++) {
        for (int y = dist; y < dim - dist; y++) {
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
        dist++;
    }
}

void creerCaree(Tableau<Cellule> &univers, int numero, int dim) {
	for (int i = 0; i < dim; i++) {
        for (int y = 0; y < dim; y++) {
            Cellule temp = ::Cellule(numero, i, y);
            univers.ajouter(temp);
        }
    }
}

void creerUnivers(Tableau<Cellule> &univers, Tableau<Cellule> &portails, istream &is) {
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
        portails.ajouter(c1);
        portails.ajouter(c2);
    }
}

int traiterRequetes(Tableau<Cellule> &univers, Tableau<Cellule> &portails, istream &is) {
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
    Tableau<Cellule> portails;
    creerUnivers(univers, portails, funivers);

    // Lecture des requ??tes
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

