/* Squelette pour classe générique Tableau<T>.
 * Lab3 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://cria2.uqam.ca/INF3105/lab3/
 */

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>

template<class T>
class Tableau {

public:
    Tableau(int capacite_initiale = 100);

    Tableau(const Tableau &);

    ~Tableau();

    // Ajouter un element à la fin
    void ajouter(const T &element);

    // Vider le tableau
    void vider();

    // Retourne le nombre d'éléments dans le tableau
    int taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void inserer(const T &element, int index = 0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void enlever(int index = 0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int chercher(const T &element);

    const T &operator[](int index) const;

    T &operator[](int index);

    bool operator==(const Tableau<T> &autre) const;

    Tableau<T> &operator=(const Tableau<T> &autre);

    void redimensionner(int nouvCapacite);

    void afficher();

private:
    T *elements;
    int nbElements;
    int capacite;

};


// ---------- Définitions -------------


template<class T>
Tableau<T>::Tableau(int capacite_) {
    elements = new T[capacite_];
    nbElements = 0;
    capacite = capacite_;
}

template<class T>
Tableau<T>::Tableau(const Tableau &autre) {
    elements = new T[autre.capacite];
    nbElements = autre.nbElements;
    capacite = autre.capacite;
    for (int i = 0; i < nbElements; i++) {
        elements[i] = autre[i];
    }
}

template<class T>
Tableau<T>::~Tableau() {
    delete[]elements;
}

template<class T>
int Tableau<T>::taille() const {
    return nbElements;
}

template<class T>
void Tableau<T>::afficher() {
    std::cout << "[ ";
    for (int i = 0; i < nbElements; i++) {
        std::cout << elements[i] << ", ";
    }
    std::cout << " ]" << std::endl;
}

template<class T>
void Tableau<T>::redimensionner(int nouvCapacite) {
    capacite = nouvCapacite;
    T *temp = new T[capacite];
    for (int i = 0; i < nbElements; i++)
        temp[i] = elements[i];
    delete[] elements;
    elements = temp;
}


template<class T>
void Tableau<T>::ajouter(const T &item) {
    if (nbElements == capacite) {
        redimensionner(capacite * 2);
    }
    elements[nbElements++] = item;
}

template<class T>
void Tableau<T>::inserer(const T &element, int index) {
    if (nbElements == capacite) {
        redimensionner(capacite * 2);
    }
    for (int i = nbElements + 1; i > index; i--) {
        elements[i] = elements[i - 1];
    }
    elements[index] = element;
    nbElements += 1;
}

template<class T>
void Tableau<T>::enlever(int index) {
    for (int i = index + 1; i < nbElements; i++) {
        elements[i - 1] = elements[i];
        // todo check the elements[-1] that could happen
    }
    nbElements--;
}

template<class T>
int Tableau<T>::chercher(const T &element) {
    for (int i = 0; i < nbElements; ++i) {
        if (elements[i] == element) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Tableau<T>::vider() {
    for (int i = 0; i < nbElements; ++i) {
        elements[i] = 0;
    }
    nbElements = 0;
}


template<class T>
const T &Tableau<T>::operator[](int index) const {
    assert(index < nbElements);
    return elements[index];
}

template<class T>
T &Tableau<T>::operator[](int index) {
    assert(index < nbElements);
    return elements[index];
}

template<class T>
Tableau<T> &Tableau<T>::operator=(const Tableau<T> &autre) {
    if (this == &autre) {
        return *this;
    } else {
        nbElements = autre.nbElements;
        if (autre.capacite > capacite) {
            delete[] elements;
            elements = new T[autre.capacite];
            capacite = autre.capacite;
        }
    }
    for (int i = 0; i < autre.nbElements; ++i) {
        elements[i] = autre.elements[i];

    }
    return *this;
}

template<class T>
bool Tableau<T>::operator==(const Tableau<T> &autre) const {
    if (nbElements != autre.nbElements) {
        return false;
    } else {
        for (int i = 0; i < nbElements; ++i) {
            if (elements[i] != autre.elements[i]) return false;
        }
        return true;
    }
}


#endif //define _TABLEAU___H_
